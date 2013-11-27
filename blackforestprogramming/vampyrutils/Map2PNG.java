package blackforestprogramming.vampyrutils;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.File;
import javax.imageio.ImageIO;
import java.awt.Graphics2D;

public class Map2PNG {
    /**
     * Determine whether the given string is a valid positive integer, that is,
     * whether `Integer.parseInt` would through an exception.
     *
     * @TODO Split into Shared.java?
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

    /**
     * Given a command-line, determine whether it is valid.
     *
     * @remarks Prints to stdout what is wrong with the given command-line.
     * @param args An array of strings representing the command-line.
     * @return true if valid, false otherwise
     */
    private static boolean areArgsValid( String[] args ) {
        // make sure enough args are given
        if ( args.length != 6 ) {
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
        
        // make sure the tilesets exist
        f = new File( args[ 3 ] );
        if ( !f.exists() ) {
            System.out.println( "Universal tileset file doesn't exist!" );
            return false;
        }
        
        f = new File( args[ 4 ] );
        if ( !f.exists() ) {
            System.out.println( "Map-specific tileset file doesn't exist!" );
            return false;
        }
        
        return true;
        // TODO: Check if output file exists and ask if want to overwite.
    }

    /**
     * Parrot the given command-line parameters to stdout.
     */
    private static void print_parameters( String input, int width, int height, String univ, String tileset, String output ) {
        System.out.println( "input file = " + input );
        System.out.println( "width = " + width );
        System.out.println( "height = " + height );
        System.out.println( "universal tileset = " + univ );
        System.out.println( "map tileset = " + tileset );
        System.out.println( "output file = " + output );
        System.out.println( "" );
    }

    /**
     * Print the program usage to stdout.
     */
    private static void print_usage() {
        // java ... input.map width height univ.png tileset.png output.png
        System.out.println( "see README.md for proper usage" );
    }

    /**
     * Draw the map from the data with the given tilesets.
     *
     * @remark Dimensions of the map are taken from the given data array. The
     *         grid is assumed to be 18x18.
     * @param data The map data.
     * @param univset The universal tileset.
     * @param tileset The map-specific tileset.
     * @return A BufferedImage of the map.
     */
    public static BufferedImage drawMap( byte[][] data, BufferedImage univset, BufferedImage tileset ) {
        // grid is hard-coded to be 18x18; deal with it
        int grid = 18;
        
        int width = data[ 0 ].length * grid;
        int height = data.length * grid;
        
        // create the map; remember: data is (y, x)!
        BufferedImage map = new BufferedImage( width, height, BufferedImage.TYPE_INT_RGB );
        Graphics2D g2d = map.createGraphics();

        // get drawing!        
        for ( int x = 0 ; x < data[ 0 ].length ; x++ ) {
            for ( int y = 0 ; y < data.length ; y++ ) {
                // get the square we are drawing
                byte index = data[ y ][ x ];
                
                // determine which tileset to draw from
                BufferedImage img = null;
                if ( index < 8 ) {
                    img = univset;
                } else {
                    img = tileset;
                    index -= 8;
                }

                // set up vars because function is very long
                int dx1 = x * grid;
                int dy1 = y * grid;
                int dx2 = ( x + 1 ) * grid;
                int dy2 = ( y + 1 ) * grid;
                
                int sx1 = index * grid;
                int sx2 = ( index + 1 ) * grid;
                
                // draw
                g2d.drawImage( img, dx1, dy1, dx2, dy2, sx1, 0, sx2, grid, null );
            }
        }
        
        return map;        
    }

    /**
     * Main
     */
    public static void main( String[] args ) {
        System.out.println( "" );
        System.out.println( "Map2PNG" );
        
        // check for valid command-line arguments; stop if not valid
        if ( !areArgsValid( args ) ) {
            print_usage();
            System.exit( 1 );
        }
        
        // now command-line should be valid; extract the info
        String input = args[ 0 ];
        int width = Integer.parseInt( args[ 1 ] );
        int height = Integer.parseInt( args[ 2 ] );
        String univ = args[ 3 ];
        String tileset = args[ 4 ];
        String output = args[ 5 ];

        // for some extra verbosity
        print_parameters( input, width, height, univ, tileset, output );
        
        try {
            // load the data
            System.out.println( "Loading map data..." );
            byte data[][] = Con2PNG.loadConData( input, width, height );
            
            // load the tilesets
            System.out.println( "Loading tilesets:" );
            System.out.println( "Universal..." );
            BufferedImage univTile = ImageIO.read( new File( univ ) );
            System.out.println( "Map-specific..." );
            BufferedImage mapTile = ImageIO.read( new File( tileset ) );
            
            // apply the palette to the data
            System.out.println( "Drawing map..." );
            BufferedImage map = drawMap( data, univTile, mapTile );
            
            // save image
            System.out.println( "Saving to output file..." );
            ImageIO.write( map, "PNG", new File( output ) );
            
            System.out.println( "Done!" );
            System.out.println( "" );
        } catch ( IOException ioe ) {
            // oh no! just dump stack for now
            ioe.printStackTrace();
            System.exit( 1 );
        }
    }
}
