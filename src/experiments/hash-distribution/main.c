// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
//
// #define ITERATION_COUNT 1000000
// #define GRANULARITY     1000
// #define STRING_LENGTH   100
//
// const char * output_file_a = "/tmp/rill-hash-distribution-a";
// const char * output_file_b = "/tmp/rill-hash-distribution-b";
// const char * output_file_c = "/tmp/rill-hash-distribution-c";
// const char * output_file_d = "/tmp/rill-hash-distribution-d";
//
// size_t rmap_hash_a ( uint8_t * key ) {
//     // http://www.partow.net/programming/hashfunctions/#SDBMHashFunction
//     size_t hash = 0;
//     uint8_t c;
//     while ( ( c = *key++ ) )
//         hash = c + ( hash << 6 ) + ( hash << 16 ) - hash;
//     return hash;
// }
//
// size_t rmap_hash_b ( uint8_t * key ) {
//     // http://www.partow.net/programming/hashfunctions/#DJBHashFunction
//     size_t hash = 5381;
//     uint8_t c;
//     while ( ( c = *key++ ) )
//         hash = ( hash << 5 ) + hash + c;
//     return hash;
// }
//
// size_t rmap_hash_c ( uint8_t * key ) {
//     // ...something I made up, twiddling constants from B.
//     size_t hash = 56923;
//     uint8_t c;
//     while ( ( c = *key++ ) )
//         hash = hash;
//     return hash;
// }
//
// size_t rmap_hash_d ( uint8_t * key ) {
//     size_t hash = 0;
//     uint8_t c;
//     while ( ( c = *key++ ) )
//         hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + c;
//     return hash;
// }
//
// void mutate_string( uint8_t * str ) {
//
//     for ( size_t i = 0; i < STRING_LENGTH; i++ ) {
//         str[ rand() % STRING_LENGTH ] += 2;
//         if ( str[ rand() % STRING_LENGTH ] == 0 )
//             str[ rand() % STRING_LENGTH ] += 11;
//     }
//     for ( size_t i = 0; i < STRING_LENGTH; i++ ) {
//         str[ rand() % STRING_LENGTH ]--;
//         if ( str[ rand() % STRING_LENGTH ] == 0 )
//             str[ rand() % STRING_LENGTH ] += 67;
//     }
//
// }
//
// int main ( int argc, char ** argv ) {
//
//     srand( time( NULL ) );
//     size_t data[ GRANULARITY ];
//     uint8_t * buffer = calloc( sizeof( uint8_t ), STRING_LENGTH + 1 );
//     buffer[ STRING_LENGTH + 1 ] = 0;
//     FILE * out;
//
//     for ( size_t i = 0; i < ITERATION_COUNT; i++ ) {
//         data[ rmap_hash_a( buffer ) % GRANULARITY ]++;
//         mutate_string( buffer );
//     }
//     if ( ( out = fopen( output_file_a, "w" ) ) == NULL ) {
//         printf( "Couldn't write to %s.\n", output_file_a );
//         return 1;
//     }
//     for ( size_t i = 0; i < GRANULARITY; i++ ) {
//         fprintf( out, "%lu\n", data[ i ] );
//     }
//     fclose( out );
//
//     free( buffer );
// }
