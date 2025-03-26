#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>

#include "string.h"
#include "qqwing.h"

#if HAVE_GETTIMEOFDAY == 1
  #include <sys/time.h>
#else
  #include <time.h>
#endif

struct sudoku_board_t {
  bool ( *set_puzzle )( self_t, int* init_puzzle );
  const int* ( *get_puzzle )( self_t self );
  const int* ( *get_solution )( self_t self );
  void ( *print_puzzle )( self_t self );
  void ( *print_solution )( self_t self );
  bool ( *solve )( self_t self );
  int ( *count_solutions )( self_t self, bool );
  bool ( *has_unique_solution )( self_t self );
  bool ( *is_solved )( self_t self );
  void ( *print_solve_history )( self_t self );
  void ( *set_record_history )( self_t self, bool rec_history );
  void ( *set_log_history )( self_t self, bool log_hist );
  void ( *set_print_style )( self_t self, print_style_t ps );
  bool ( *generate_puzzle_symmetry )( self_t self, symmetry_t symmetry );
  int ( *get_given_count )( self_t self );
  int ( *get_single_count )( self_t self );
  int ( *get_hidden_single_count )( self_t self );
  int ( *get_naked_pair_count )( self_t self );
  int ( *get_hidden_pair_count )( self_t self );
  int ( *get_box_line_reduction_count )( self_t self );
  int ( *get_pointing_pair_triple_count )( self_t self );
  int ( *get_guess_count )( self_t self );
  int ( *get_backtrack_count )( self_t self );
  void ( *print_solve_instructions )( self_t self );
  difficulty_t ( *get_difficulty )( self_t self );
  char* ( *get_difficulty_as_string )( self_t self );
};

long get_microseconds( void );
bool read_puzzle_from_stdin( int* puzzle );
void print_help( void );
void print_version( void );
void print_about( void );

/**
 * Main method -- the entry point into the program.
 * Run with --help as an argument for usage and documentation
 */
int
main( int argc, char *argv[] )
{
  // Start time for the application for timing
  long application_start_time = get_microseconds();

  // The number of puzzles solved or generated.
  int puzzle_count = 0;

  enum action_t {
    ACTION_NONE,
    ACTION_GENERATE,
    ACTION_SOLVE
  };

  // defaults for options
  bool print_puzzle = false;
  bool print_solution = false;
  bool print_history = false;
  bool print_instructions = false;
  bool timer = false;
  bool count_solutions = false;
  enum action_t action = ACTION_NONE;
  bool log_history = false;
  print_style_t print_style = READABLE;
  int number_to_generate = 1;
  bool print_stats = false;
  difficulty_t difficulty = UNKNOWN;
  symmetry_t symmetry = SYMMETRY_NONE;

  // Read the arguments and set the options
  for ( int i = 1; i < argc; i++ ) {
    if ( !strcmp( argv[i],"--puzzle" )) {
      print_puzzle = true;
    } else if ( !strcmp( argv[i],"--nopuzzle" )) {
      print_puzzle = false;
    } else if ( !strcmp( argv[i],"--solution" )) {
      print_solution = true;
    } else if ( !strcmp( argv[i],"--nosolution" )) {
      print_solution = false;
    } else if ( !strcmp( argv[i],"--history" )) {
      print_history = true;
    } else if ( !strcmp( argv[i],"--nohistory" )) {
      print_history = false;
    } else if ( !strcmp( argv[i],"--instructions" )) {
      print_instructions = true;
    } else if ( !strcmp( argv[i],"--noinstructions" )) {
      print_instructions = false;
    } else if ( !strcmp( argv[i],"--stats" )) {
      print_stats = true;
    } else if ( !strcmp( argv[i],"--nostats" )) {
      print_stats = false;
    #if HAVE_GETTIMEOFDAY == 1
      } else if ( !strcmp( argv[i],"--timer" )) {
        timer = true;
      } else if ( !strcmp( argv[i],"--notimer" )) {
        timer = false;
    #endif
    } else if ( !strcmp( argv[i],"--count-solutions" )) {
      count_solutions = true;
    } else if ( !strcmp( argv[i],"--nocount-solutions" )) {
      count_solutions = false;
    } else if ( !strcmp( argv[i],"--generate" )) {
      action = ACTION_GENERATE;
      print_puzzle = true;
      if ( ( i + 1 ) < argc && argv[i+1][0] != '-' ) {
        number_to_generate = atoi( argv[i+1] );
        if ( number_to_generate <= 0 ) {
          fprintf( stdout, "%s%s\n", "Bad number of puzzles to generate: ", argv[i+1] );
          return 1;
        }
        i++;
      }
    } else if ( !strcmp( argv[i],"--difficulty" )) {
      if ( argc <= i+1 ) {
        fprintf( stdout, "%s\n", "Please specify a difficulty." );
        return 1;
      } else if ( !strcmp( argv[i+1],"simple" )) {
        difficulty = SIMPLE;
      } else if ( !strcmp( argv[i+1],"easy" )) {
        difficulty = EASY;
      } else if ( !strcmp( argv[i+1],"intermediate" )) {
        difficulty = INTERMEDIATE;
      } else if ( !strcmp( argv[i+1],"expert" )) {
        difficulty = EXPERT;
      } else if ( !strcmp( argv[i+1],"any" )) {
        difficulty = UNKNOWN;
      } else {
        fprintf( stdout, "%s%s\n", "Difficulty expected to be simple, easy, intermediate, expert, or any, not ", argv[i+1] );
        return 1;
      }
      i++;
    } else if ( !strcmp( argv[i],"--symmetry" )) {
      if ( argc <= i+1 ) {
        fprintf( stdout, "%s\n", "Please specify a symmetry." );
        return 1;
      } else if ( !strcmp( argv[i+1],"none" )) {
        symmetry = SYMMETRY_NONE;
      } else if ( !strcmp( argv[i+1],"rotate90" )) {
        symmetry = SYMMETRY_ROTATE90;
      } else if ( !strcmp( argv[i+1],"rotate180" )) {
        symmetry = SYMMETRY_ROTATE180;
      } else if ( !strcmp( argv[i+1],"mirror" )) {
        symmetry = SYMMETRY_MIRROR;
      } else if ( !strcmp( argv[i+1],"flip" )) {
        symmetry = SYMMETRY_FLIP;
      } else if ( !strcmp( argv[i+1],"random" )) {
        symmetry = SYMMETRY_RANDOM;
      } else {
        fprintf( stdout, "%s%s\n", "Symmetry expected to be none, rotate90, rotate180, mirror, flip, or random, not ", argv[i+1] );
        return 1;
      }
      i++;
    } else if ( !strcmp( argv[i],"--solve" )) {
      action = ACTION_SOLVE;
      print_solution = true;
    } else if ( !strcmp( argv[i],"--log-history" )) {
      log_history = true;
    } else if ( !strcmp( argv[i],"--nolog-history" )) {
      log_history = false;
    } else if ( !strcmp( argv[i],"--one-line" )) {
      print_style=ONE_LINE;
    } else if ( !strcmp( argv[i],"--compact" )) {
      print_style=COMPACT;
    } else if ( !strcmp( argv[i],"--readable" )) {
      print_style=READABLE;
    } else if ( !strcmp( argv[i],"--csv" )) {
      print_style=CSV;
    } else if ( !strcmp( argv[i],"-n" ) || !strcmp( argv[i],"--number" )) {
      if ( i+1 < argc ) {
        number_to_generate = atoi( argv[i+1] );
        i++;
      } else {
        fprintf( stdout, "%s\n", "Please specify a number." );
        return 1;
      }
    } else if ( !strcmp( argv[i],"-h" ) || !strcmp( argv[i],"--help" ) || !strcmp( argv[i],"help" ) || !strcmp( argv[i],"?" )) {
      print_help();
      return 0;
    } else if ( !strcmp( argv[i],"--version" )) {
      print_version();
      return 0;
    } else if ( !strcmp( argv[i],"--about" )) {
      print_about();
      return 0;
    } else {
      fprintf( stdout, "%s%s%s\n", "Unknown argument: '", argv[i], "'" );
      print_help();
      return 1;
    }
  }

  if ( action == ACTION_NONE ) {
    fprintf( stdout, "%s\n", "Either --solve or --generate must be specified." );
    print_help();
    return 1;
  }

  // Initialize the random number generator
  srand ( time( NULL ));

  // If printing out CSV, print a header
  if ( print_style == CSV ) {
    if ( print_puzzle ) fprintf( stdout, "%s", "Puzzle," );
    if ( print_solution ) fprintf( stdout, "%s", "Solution," );
    if ( print_history ) fprintf( stdout, "%s", "Solve History," );
    if ( print_instructions ) fprintf( stdout, "%s", "Solve Instructions," );
    if ( count_solutions ) fprintf( stdout, "%s", "Solution Count," );
    if ( timer ) fprintf( stdout, "%s", "Time ( milliseconds )," );
    if ( print_stats ) fprintf( stdout, "%s", "Givens,Singles,Hidden Singles,Naked Pairs,Hidden Pairs,Pointing Pairs/Triples,Box/Line Intersections,Guesses,Backtracks,Difficulty" );
    fprintf( stdout, "%s\n", "" );
  }

  // Create a new puzzle board
  // and set the options
  sudoku_board_t* ss = new_sudoku_board();
  ss->set_record_history( ss, print_history || print_instructions || print_stats || difficulty != UNKNOWN );
  ss->set_log_history( ss, log_history );
  ss->set_print_style( ss, print_style );

  // Solve puzzle or generate puzzles
  // until end of input for solving, or
  // until we have generated the specified number.
  bool done = false;
  int number_generated = 0;
  while ( !done ) {
    // record the start time for the timer.
    long puzzle_start_time = get_microseconds();

    // iff something has been printed for this particular puzzle
    bool printed_something = false;

    // Record whether the puzzle was possible or not,
    // so that we don't try to solve impossible givens.
    bool have_puzzle = false;
    if ( action == ACTION_GENERATE ) {
      // Generate a puzzle
      have_puzzle = ss->generate_puzzle_symmetry( ss, symmetry );
      if ( !have_puzzle && print_puzzle ) {
        fprintf( stdout, "%s", "Could not generate puzzle." );
        if ( print_style==CSV ) {
          fprintf( stdout, "%s", "," );
        } else {
          puts( "" );
        }
        printed_something = true;
      }
    } else {
      // Read the next puzzle on STDIN
      int* puzzle = ( int* )malloc( sizeof( int ) * BOARD_SIZE );
      if ( read_puzzle_from_stdin( puzzle )) {
        have_puzzle = ss->set_puzzle( ss, puzzle );
        if ( !have_puzzle ) {
          if ( print_puzzle ) {
            ss->print_puzzle( ss );
            printed_something = true;
          }
          if ( print_solution ) {
            fprintf( stdout, "%s", "Puzzle is not possible." );
            if ( print_style == CSV ) {
              fprintf( stdout, "%s", "," );
            } else {
              puts( "" );
            }
            printed_something = true;
          }
        }
      } else {
        // Set loop to terminate when nothing is left on STDIN
        have_puzzle = false;
        done = true;
      }
      free( puzzle );
    }

    int solutions = 0;

    if ( have_puzzle ) {

      // Count the solutions if requested.
      // ( Must be done before solving, as it would
      // mess up the stats. )
      if ( count_solutions ) {
        solutions = ss->count_solutions( ss, false );
      }

      // Solve the puzzle
      if ( print_solution || print_history || print_stats || print_instructions || difficulty != UNKNOWN ) {
        ss->solve( ss );
      }

      // Bail out if it didn't meet the difficulty standards for generation
      if ( action == ACTION_GENERATE ) {
        if ( difficulty != UNKNOWN && difficulty != ss->get_difficulty( ss ) ) {
          have_puzzle = false;
        } else {
          number_generated++;
          // Set loop to terminate if enough have been generated.
          if ( number_generated >= number_to_generate ) done = true;
        }
      }
    }

    // Check have_puzzle again, it may have changed based on difficulty
    if ( have_puzzle ) {

      // With a puzzle now in hand and possibly solved
      // print out the solution, stats, etc.
      printed_something = true;

      // Record the end time for the timer.
      long puzzle_done_time = get_microseconds();

      // Print the puzzle itself.
      if ( print_puzzle ) ss->print_puzzle( ss );

      // Print the solution if there is one
      if ( print_solution ) {
        if ( ss->is_solved( ss ) ) {
          ss->print_solution( ss );
        } else {
          fprintf( stdout, "%s", "Puzzle has no solution." );
          if ( print_style==CSV ) {
            fprintf( stdout, "%s", "," );
          } else {
            puts( "" );
          }
        }
      }

      // Print the steps taken to solve or attempt to solve the puzzle.
      if ( print_history ) ss->print_solve_history( ss );
      // Print the instructions for solving the puzzle
      if ( print_instructions ) ss->print_solve_instructions( ss );

      // Print the number of solutions to the puzzle.
      if ( count_solutions ) {
        if ( print_style == CSV ) {
          fprintf( stdout, "%d%s", solutions, "," );
        } else {
          if ( solutions == 0 ) {
            fprintf( stdout, "%s\n", "There are no solutions to the puzzle." );
          } else if ( solutions == 1 ) {
            fprintf( stdout, "%s\n", "The solution to the puzzle is unique." );
          } else {
            fprintf( stdout, "%s%d%s\n", "There are ", solutions, " solutions to the puzzle." );
          }
        }
      }

      // Print out the time it took to solve the puzzle.
      if ( timer ) {
        double t = ( (double )( puzzle_done_time - puzzle_start_time ) ) / 1000.0;
        if ( print_style == CSV ) {
          fprintf( stdout, "%.3f%s", t, "," );
        } else {
          fprintf( stdout, "%s%.3f%s\n", "Time: ", t, " milliseconds" );
        }
      }

      // Print any stats we were able to gather while solving the puzzle.
      if ( print_stats ) {
        int given_count = ss->get_given_count( ss );
        int single_count = ss->get_single_count( ss );
        int hidden_single_count = ss->get_hidden_single_count( ss );
        int naked_pair_count = ss->get_naked_pair_count( ss );
        int hidden_pair_count = ss->get_hidden_pair_count( ss );
        int pointing_pair_triple_count = ss->get_pointing_pair_triple_count( ss );
        int box_reduction_count = ss->get_box_line_reduction_count( ss );
        int guess_count = ss->get_guess_count( ss );
        int backtrack_count = ss->get_backtrack_count( ss );
        char* difficulty_string = ss->get_difficulty_as_string( ss );
        if ( print_style == CSV ) {
          fprintf( stdout, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,",
              given_count, single_count, hidden_single_count,
              naked_pair_count, hidden_pair_count,
              pointing_pair_triple_count, box_reduction_count,
              guess_count, backtrack_count,
              difficulty_string );
        } else {
          fprintf( stdout, "%s%d\n", "Number of Givens: ",                 given_count );
          fprintf( stdout, "%s%d\n", "Number of Singles: ",                single_count );
          fprintf( stdout, "%s%d\n", "Number of Hidden Singles: ",         hidden_single_count );
          fprintf( stdout, "%s%d\n", "Number of Naked Pairs: ",            naked_pair_count );
          fprintf( stdout, "%s%d\n", "Number of Hidden Pairs: ",           hidden_pair_count );
          fprintf( stdout, "%s%d\n", "Number of Pointing Pairs/Triples: ", pointing_pair_triple_count );
          fprintf( stdout, "%s%d\n", "Number of Box/Line Intersections: ", box_reduction_count );
          fprintf( stdout, "%s%d\n", "Number of Guesses: ",                guess_count );
          fprintf( stdout, "%s%d\n", "Number of Backtracks: ",             backtrack_count );
          fprintf( stdout, "%s%s\n", "Difficulty: ",                       difficulty_string );
        }
      }
      puzzle_count++;
    }
    if ( printed_something && print_style == CSV ) {
      puts( "" );
    }
  }

  free( ss );

  long application_done_time = get_microseconds();
  if ( timer ) {
    double t = ( ( double )( application_done_time - application_start_time ) ) / 1000000.0;
    fprintf( stdout, "%d%s%s%s%s%s%.3f%s\n", puzzle_count, " puzzle", ( ( puzzle_count == 1 ) ? "" : "s" ),
                              " ", ( action == ACTION_GENERATE ? "generated" : "solved" ), " in ",
                              t, " seconds." );
  }

  return 0;
}

void
print_version( void )
{
  fprintf( stdout, "%s\n", PACKAGE_STRING );
}

void
print_about( void )
{
  fprintf( stdout, "%s\n", "qqwing - Sudoku solver and generator" );
  fprintf( stdout, "%s\n", "Copyright ( C ) 2006-2014 Stephen Ostermiller http://ostermiller.org/" );
  fprintf( stdout, "%s\n", "Copyright ( C ) 2007 Jacques Bensimon ( jacques@ipm.com )" );
  fprintf( stdout, "%s\n", "Copyright ( C ) 2011 Jean Guillerez ( j.guillerez - orange.fr )" );
  fprintf( stdout, "%s\n", "Copyright ( C ) 2014 Michael Catanzaro ( mcatanzaro@gnome.org )" );
  fprintf( stdout, "%s\n", "" );
  fprintf( stdout, "%s\n", "This program is free software; you can redistribute it and/or modify" );
  fprintf( stdout, "%s\n", "it under the terms of the GNU General Public License as published by" );
  fprintf( stdout, "%s\n", "the Free Software Foundation; either version 2 of the License, or" );
  fprintf( stdout, "%s\n", "( at your option ) any later version." );
  fprintf( stdout, "%s\n", "" );
  fprintf( stdout, "%s\n", "This program is distributed in the hope that it will be useful," );
  fprintf( stdout, "%s\n", "but WITHOUT ANY WARRANTY; without even the implied warranty of" );
  fprintf( stdout, "%s\n", "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" );
  fprintf( stdout, "%s\n", "GNU General Public License for more details." );
  fprintf( stdout, "%s\n", "" );
  fprintf( stdout, "%s\n", "You should have received a copy of the GNU General Public License along" );
  fprintf( stdout, "%s\n", "with this program; if not, write to the Free Software Foundation, Inc.," );
  fprintf( stdout, "%s\n", "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA." );
}

void
print_help( void )
{
  fprintf( stdout, "%s\n", "qqwing <options>" );
  fprintf( stdout, "%s\n", "Sudoku solver and generator." );
  fprintf( stdout, "%s\n", "  --generate <num>     Generate new puzzles" );
  fprintf( stdout, "%s\n", "  --solve              Solve all the puzzles from standard input" );
  fprintf( stdout, "%s\n", "  --difficulty <diff>  Generate only simple, easy, intermediate, expert, or any" );
  fprintf( stdout, "%s\n", "  --symmetry <sym>     Symmetry: none, rotate90, rotate180, mirror, flip, or random" );
  fprintf( stdout, "%s\n", "  --puzzle             Print the puzzle ( default when generating )" );
  fprintf( stdout, "%s\n", "  --nopuzzle           Do not print the puzzle ( default when solving )" );
  fprintf( stdout, "%s\n", "  --solution           Print the solution ( default when solving )" );
  fprintf( stdout, "%s\n", "  --nosolution         Do not print the solution ( default when generating )" );
  fprintf( stdout, "%s\n", "  --stats              Print statistics about moves used to solve the puzzle" );
  fprintf( stdout, "%s\n", "  --nostats            Do not print statistics ( default )" );
  #if HAVE_GETTIMEOFDAY == 1
    fprintf( stdout, "%s\n", "  --timer              Print time to generate or solve each puzzle" );
    fprintf( stdout, "%s\n", "  --notimer            Do not print solve or generation times ( default )" );
  #endif
  fprintf( stdout, "%s\n", "  --count-solutions    Count the number of solutions to puzzles" );
  fprintf( stdout, "%s\n", "  --nocount-solutions  Do not count the number of solutions ( default )" );
  fprintf( stdout, "%s\n", "  --history            Print trial and error used when solving" );
  fprintf( stdout, "%s\n", "  --nohistory          Do not print trial and error to solve ( default )" );
  fprintf( stdout, "%s\n", "  --instructions       Print the steps ( at least 81 ) needed to solve the puzzle" );
  fprintf( stdout, "%s\n", "  --noinstructions     Do not print steps to solve ( default )" );
  fprintf( stdout, "%s\n", "  --log-history        Print trial and error to solve as it happens" );
  fprintf( stdout, "%s\n", "  --nolog-history      Do not print trial and error  to solve as it happens" );
  fprintf( stdout, "%s\n", "  --one-line           Print puzzles on one line of 81 characters" );
  fprintf( stdout, "%s\n", "  --compact            Print puzzles on 9 lines of 9 characters" );
  fprintf( stdout, "%s\n", "  --readable           Print puzzles in human readable form ( default )" );
  fprintf( stdout, "%s\n", "  --csv                Output CSV format with one line puzzles" );
  fprintf( stdout, "%s\n", "  --help               Print this message" );
  fprintf( stdout, "%s\n", "  --about              Author and license information" );
  fprintf( stdout, "%s\n", "  --version            Display current version number" );
}

bool
read_puzzle_from_stdin( int* puzzle )
{
  int read = 0;
  while ( read < BOARD_SIZE ) {
    char c = getchar();
    if ( c == EOF ) return false;
    if ( c >= '1' && c <='9' ) {
      puzzle[read] = c-'0';
      read++;
    }
    if ( c == '.' || c == '0' ) {
      puzzle[read] = 0;
      read++;
    }
  }
  return true;
}

long
get_microseconds( void )
{
  #if HAVE_GETTIMEOFDAY == 1
    struct timeval tv;
    gettimeofday( &tv, NULL );
    return tv.tv_sec*1000000+tv.tv_usec;
  #else
    return 0;
  #endif
}
