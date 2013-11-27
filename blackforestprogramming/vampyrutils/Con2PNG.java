package blackforestprogramming.vampyrutils;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.File;
import javax.imageio.ImageIO;
import java.awt.Graphics2D;

/**
 * This class provides many static methods, all with the purpose of turning
 * image files from Vampyr into .PNG files.
 *
 * The class cannot be instantiated. A CLI is programmed into the `main` method.
 * 
 * @author Michael Hitchens
 * @see Map2PNG
 */
public class Con2PNG {

    /**
     * Hide the constructor; the class should never be instantiated.
     */
    private Con2PNG() {}

    /**
     * Determine whether the given string is a valid positive integer, that is,
     * whether `Integer.parseInt` would through an exception.
     *
     * @param str The String to check
     * @return true if the string is an integer, false otherwise
     */
    public static boolean isStringInteger( String str ) {
        // special case where given an empty string; not valid
        if ( str.length() == 0 ) return false;
        
        // check each character to make sure it is a digit
        for ( char chr : str.toCharArray() ) {
            if ( chr < '0' || chr > '9' ) return false;
        }
        
        // all good!
        return true;
    }
 
    /**************************************************************************
    *    PUBLIC                                                               *
    **************************************************************************/ 

    /**
     * Load the binary data from `file` and use the given dimensions to store it
     * in a rectangular array.
     *
     * @remark Data in CON files is stored (y, x), backwards from usual.
     * @param file The binary file to load.
     * @param width The width of the image.
     * @param height The height of the image.
     * @return A rectangular array of bytes representing the image.
     */
    public static byte[][] loadConData( String file, int width, int height ) throws IOException {
        byte[][] data = new byte[ height ][ width ];
        
        // open the file
        FileReader in = new FileReader( file );
        
        // read the file, throwing an error if getting EOF prematurely
        for ( int x = 0 ; x < width ; x++ ) {
            for ( int y = 0 ; y < height ; y++ ) {
                data[ y ][ x ] = ( byte )in.read();
                if ( data[ y ][ x ] == -1 ) throw new IOException( "Dimensions off; ran out of input data!" );
            }
        }
        
        // return the data
        return data; // TODO: Fill me in!
    }

    /**
     * Parse the given palette file, `file`, and turn each entry into the color
     * they represent, then stick them in an array and return it.
     *
     * @param file The palette file to parse
     * @return An array of Colors.
     */
    public static Color[] parsePaletteFile( String file ) throws IOException {
        Color ret[] = new Color[ 16 ];
        
        // open the file
        BufferedReader in = new BufferedReader( new FileReader( file ) );
        
        // for a certain number of lines in the file
        for ( int i = 0 ; i < ret.length ; i++ ) {
            int rgb[] = new int[ 3 ];
            
            // read the line and throw an error if got EOF
            String line = in.readLine();
            if ( in == null ) throw new IOException( "Malformed file content: expected another color, got EOF!" );
            
            // split the line around the commas and throw an error if not enough parts
            String parts[] = line.split( "," );
            if ( parts.length != rgb.length ) throw new IOException( "Malformed file content: need only red,green,blue!" );
            
            // for each part
            for ( int ii = 0 ; ii < parts.length ; ii++ ) {
                // if it can't be turned into an integer throw an error
                if ( !isStringInteger( parts[ ii ] ) ) throw new IOException( "Malformed file content: channel isn't a valid number!" );
                
                // if it is not a valid value throw an error
                rgb[ ii ] = Integer.parseInt( parts[ ii ] );
                if ( rgb[ ii ] < 0 || rgb[ ii ] > 255 ) throw new IOException( "Malformed file content: channel isn't a unsigned byte!" );
            }
            
            // have good data to make a color
            ret[ i ] = new Color( rgb[ 0 ], rgb[ 1 ], rgb[ 2 ] );
        }
        
        // done; close the file
        in.close();
        
        // return the colors loaded
        return ret;
    }

    /**
     * Create an image from the data by applying the color palette to it.
     *
     * @remarks Image dimensions are taken from the dimensions of the input data.
     * @param palette An array of 16 colors.
     * @param data A regtangular array of image data.
     * @return A `BufferedImage`, the result of applying the palette to each data value.
     */
    public static BufferedImage makeImageFromData( byte[][] data, Color[] palette ) {
        // create the image
        BufferedImage ret = new BufferedImage( data[ 0 ].length, data.length, BufferedImage.TYPE_INT_RGB );
        Graphics2D g2d = ret.createGraphics();
        
        for ( int x = 0 ; x < data[ 0 ].length ; x++ ) {
            for ( int y = 0 ; y < data.length ; y++ ) {
                g2d.setColor( palette[ data[ y ][ x ] ] );
                g2d.fillRect( x, y, 2, 2 );
            }
        }
        
        return ret; // TODO: Fill me in!
    }
    
    /**
     * Load the `.con` file turn it into a bitmap.
     *
     * @remark Provided for convenience for outside use; essentially calls
     *         loadConData, parsePaletteFile, and makeImageFromData.
     * @param input The input filename.
     * @param width The width of the image.
     * @param height The height of the image.
     * @param paletteFile The filename of the palette definition.
     * @return A BufferedImage
     */
    public static BufferedImage conToBitmap( String input, int width, int height, String paletteFile ) throws IOException {
        // load the data
        System.out.println( "Loading image data..." );
        byte data[][] = loadConData( input, width, height );
        
        // load the palette
        System.out.println( "Loading palette definitions..." );
        Color palette[] = parsePaletteFile( paletteFile );
        
        // apply the palette to the data
        System.out.println( "Applying palette to image data..." );
        BufferedImage image = makeImageFromData( data, palette );
        
        // return the image
        System.out.println( "Returning image..." );
        return image;
    }

    /**************************************************************************
    *    PRIVATE                                                              *
    **************************************************************************/ 

    /**
     * Given a command-line, determine whether it is valid.
     *
     * @remarks Prints to stdout what is wrong with the given command-line.
     * @param args An array of strings representing the command-line.
     * @return true if valid, false otherwise
     */
    private static boolean areArgsValid( String[] args ) {
        // make sure enough args are given
        if ( args.length != 5 ) {
            System.out.println( "Not the right number of arguments!" );
            return false;
        }
        
        // check to make sure input file exists
        File f = new File( args[ 0 ] );
        if ( !f.exists() ) {
            System.out.println( "Input file does not exist!" );
            return false;
        }
        
        // make sure width and height are integers
        if ( !isStringInteger( args[1] ) ) {
            System.out.println( "Width is not a valid integer!" );
            return false;
        }
        
        if ( !isStringInteger( args[2] ) ) {
            System.out.println( "Height is not a valid integer!" );
            return false;
        }
        
        // make sure palette file exists
        f = new File( args[ 3 ] );
        if ( !f.exists() ) {
            System.out.println( "Palette file doesn't exist!" );
            return false;
        }
        
        return true;
        // TODO: Check if output file exists and ask if want to overwite.
    }


    /**
     * Parrot the given command-line parameters to stdout.
     */
    private static void print_parameters( String input, int width, int height, String paletteFile, String output ) {
        System.out.println( "input file = " + input );
        System.out.println( "width = " + width );
        System.out.println( "height = " + height );
        System.out.println( "palette file = " + paletteFile );
        System.out.println( "output file = " + output );
        System.out.println( "" );
    }
    
    /**
     * Print the program usage to stdout.
     */
    private static void print_usage() {
        System.out.println( "see README.md for proper usage" );
    }
    
    /**************************************************************************
    *    MAIN                                                                 *
    **************************************************************************/ 
    
    /**
     * Load the data, load the colors, apply the colors to the data, and save
     * the resulting image.
     */
    public static void main( String args[] ) {
        System.out.println( "" );
        System.out.println( "Con2PNG" );
        
        // check for valid command-line arguments; stop if not valid
        if ( !areArgsValid( args ) ) {
            print_usage();
            System.exit( 1 );
        }
        
        // now command-line should be valid; extract the info
        String input = args[ 0 ];
        int width = Integer.parseInt( args[ 1 ] );
        int height = Integer.parseInt( args[ 2 ] );
        String paletteFile = args[ 3 ];
        String output = args[ 4 ];

        // for some extra verbosity
        print_parameters( input, width, height, paletteFile, output );
        
        try {
            // manipulate the data
            BufferedImage image = conToBitmap( input, width, height, paletteFile );
            
            // save image
            System.out.println( "Saving to output file..." );
            ImageIO.write( image, "PNG", new File( output ) );
            
            System.out.println( "Done!" );
            System.out.println( "" );
        } catch ( IOException ioe ) {
            // oh no! just dump stack for now
            ioe.printStackTrace();
            System.exit( 1 );
        }
    }
}
