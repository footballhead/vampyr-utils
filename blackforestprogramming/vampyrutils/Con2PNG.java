package blackforestprogramming.vampyrutils;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.File;
import javax.imageio.ImageIO;
import java.awt.Graphics2D;

public class Con2PNG {

    
    public Con2PNG( String[] args ) {
        // check for valid command-line arguments; stop if not valid
        if ( !isValidArgs( args ) ) {
            print_usage();
            System.exit( 1 );
        }
        
        // now command-line should be valid; extract the info
        String input = args[ 0 ];
        int width = Integer.parseInt( args[ 1 ] );
        int height = Integer.parseInt( args[ 2 ] );
        String palletFile = args[ 3 ];
        String output = args[ 4 ];
        
        try {
            // load the data
            byte data[][] = loadConData( input, width, height );
            
            // load the pallet
            Color pallet[] = parsePalletFile( palletFile );
            
            // apply the pallet to the data
            BufferedImage image = makeImageFromData( data, pallet );
            
            // save image
            ImageIO.write( image, "PNG", new File( output ) );
        } catch ( IOException ioe ) {
            ioe.printStackTrace();
            System.exit( 1 );
        }
    }
    
    /**
     * Given a command-line, determine whether it is valid.
     *
     * @remarks Prints to stdout what is wrong with the given command-line.
     * @param args An array of strings representing the command-line.
     * @return true if valid, false otherwise
     */
    private boolean isValidArgs( String[] args ) {
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
        
        // make sure pallet file exists
        f = new File( args[ 3 ] );
        if ( !f.exists() ) {
            System.out.println( "Pallet file doesn't exist!" );
            return false;
        }
        
        return true;
        // TODO: Check if output file exists and ask if want to overwite.
    }

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
    private byte[][] loadConData( String file, int width, int height ) throws IOException {
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
     * Parse the given pallet file, `file`, and turn each entry into the color
     * they represent, then stick them in an array and return it.
     *
     * @param file The pallet file to parse
     * @return An array of Colors.
     */
    private Color[] parsePalletFile( String file ) throws IOException {
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
     * Create an image from the data by applying the color pallet to it.
     *
     * @remarks Image dimensions are taken from the dimensions of the input data.
     * @param pallet An array of 16 colors.
     * @param data A regtangular array of image data.
     * @return A `BufferedImage`, the result of applying the pallet to each data value.
     */
    private BufferedImage makeImageFromData( byte[][] data, Color[] pallet ) {
        // create the image
        BufferedImage ret = new BufferedImage( data[ 0 ].length, data.length, BufferedImage.TYPE_INT_RGB );
        Graphics2D g2d = ret.createGraphics();
        
        for ( int x = 0 ; x < data[ 0 ].length ; x++ ) {
            for ( int y = 0 ; y < data.length ; y++ ) {
                g2d.setColor( pallet[ data[ y ][ x ] ] );
                g2d.fillRect( x, y, 2, 2 );
            }
        }
        
        return ret; // TODO: Fill me in!
    }

    /**
     * Determine whether the given string is a valid positive integer, that is,
     * whether `Integer.parseInt` would through an exception.
     *
     * @param str The String to check
     * @return true if the string is an integer, false otherwise
     */
    private static boolean isStringInteger( String str ) {
        // special case where given an empty string; not valid
        if ( str.length() == 0 ) return false;
        
        // check each character to make sure it is a digit
        for ( char chr : str.toCharArray() ) {
            if ( chr < '0' || chr > '9' ) return false;
        }
        
        // all good!
        return true;
    }
    
    /**
     * Print the program usage to stdout.
     */
    public static void print_usage() {
        System.out.println( "usage: java Driver input width height pallet output" );
    }
    
    public static void main( String args[] ) {
        new Con2PNG( args );
    }
}
