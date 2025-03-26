#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "qqwing.h"

struct _sudoku_board_t
{
  // public
  bool (*set_puzzle) (self_t self, int *init_puzzle);
  const int *(*get_puzzle) (self_t self);
  const int *(*get_solution) (self_t self);
  void (*print_puzzle) (self_t self);
  void (*print_solution) (self_t self);
  bool (*solve) (self_t self);
  int (*count_solutions) (self_t self, bool);
  bool (*has_unique_solution) (self_t self);
  bool (*is_solved) (self_t self);
  void (*print_solve_history) (self_t self);
  void (*set_record_history) (self_t self, bool rec_history);
  void (*set_log_history) (self_t self, bool log_hist);
  void (*set_print_style) (self_t self, print_style_t ps);
  bool (*generate_puzzle_symmetry) (self_t self, symmetry_t symmetry);
  int (*get_given_count) (self_t self);
  int (*get_single_count) (self_t self);
  int (*get_hidden_single_count) (self_t self);
  int (*get_naked_pair_count) (self_t self);
  int (*get_hidden_pair_count) (self_t self);
  int (*get_box_line_reduction_count) (self_t self);
  int (*get_pointing_pair_triple_count) (self_t self);
  int (*get_guess_count) (self_t self);
  int (*get_backtrack_count) (self_t self);
  void (*print_solve_instructions) (self_t self);
  difficulty_t (*get_difficulty) (self_t self);
  char *(*get_difficulty_as_string) (self_t self);

  // private
  int *puzzle;
  int *solution;
  int *solution_round;
  int *possibilities;
  int *random_board_array;
  int *random_possibility_array;

  bool record_history;
  bool log_history;

  log_list_t *solve_history;
  log_list_t *solve_instructions;

  print_style_t print_style;

  int last_solve_round;

  bool (*reset) (struct _sudoku_board_t*);
  bool (*single_solve_move) (struct _sudoku_board_t*, int);
  bool (*only_possibility_for_cell) (struct _sudoku_board_t*, int);
  bool (*only_value_in_row) (struct _sudoku_board_t*, int);
  bool (*only_value_in_column) (struct _sudoku_board_t*, int);
  bool (*only_value_in_section) (struct _sudoku_board_t*, int);
  bool (*guess) (struct _sudoku_board_t*, int, int);
  bool (*is_impossible) (struct _sudoku_board_t*);
  void (*rollback_round) (struct _sudoku_board_t*, int);
  bool (*pointing_row_reduction) (struct _sudoku_board_t*, int);
  bool (*row_box_reduction) (struct _sudoku_board_t*, int);
  bool (*col_box_reduction) (struct _sudoku_board_t*, int);
  bool (*pointing_column_reduction) (struct _sudoku_board_t*, int);
  bool (*hidden_pair_in_row) (struct _sudoku_board_t*, int);
  bool (*hidden_pair_in_column) (struct _sudoku_board_t*, int);
  bool (*hidden_pair_in_section) (struct _sudoku_board_t*, int);
  void (*mark) (struct _sudoku_board_t*, int, int, int);
  int (*find_position_with_fewest_possibilities) (struct _sudoku_board_t*);
  bool (*handle_naked_pairs) (struct _sudoku_board_t*, int);
  int (*count_possibilities) (struct _sudoku_board_t*, int);
  bool (*are_possibilities_same) (struct _sudoku_board_t*, int, int);
  void (*add_history_item) (struct _sudoku_board_t*, log_item_t *const);
  void (*shuffle_random_arrays) (struct _sudoku_board_t*);
  void (*print) (struct _sudoku_board_t*, const int *const);
  void (*rollback_non_guesses) (struct _sudoku_board_t*);
  void (*clear_puzzle) (struct _sudoku_board_t*);
  void (*print_history) (struct _sudoku_board_t*, log_list_t *);
  bool (*remove_possibilities_in_one_from_two) (struct _sudoku_board_t*, int,
                                                int, int);
};

typedef struct _sudoku_board_t * _self_t;

// public
bool set_puzzle (self_t self, int *init_puzzle);
const int *get_puzzle (self_t self);
const int *get_solution (self_t self);
void print_puzzle (self_t self);
void print_solution (self_t self);
bool solve (self_t self);
int count_solutions (self_t self, bool limited);
bool has_unique_solution (self_t self);
bool is_solved (self_t self);
void print_solve_history (self_t self);
void set_record_history (self_t self, bool rec_history);
void set_log_history (self_t self, bool log_hist);
void set_print_style (self_t self, print_style_t ps);
bool generate_puzzle_symmetry (self_t self, symmetry_t symmetry);
int get_given_count (self_t self);
int get_single_count (self_t self);
int get_hidden_single_count (self_t self);
int get_naked_pair_count (self_t self);
int get_hidden_pair_count (self_t self);
int get_box_line_reduction_count (self_t self);
int get_pointing_pair_triple_count (self_t self);
int get_guess_count (self_t self);
int get_backtrack_count (self_t self);
void print_solve_instructions (self_t self);
difficulty_t get_difficulty (self_t self);
char *get_difficulty_as_string (self_t self);

// private
const int* _get_puzzle(_self_t self);
bool _set_puzzle(_self_t self, int *init_puzzle);
const int* _get_solution(_self_t self);
int _get_single_count(_self_t self);
int _get_hidden_single_count(_self_t self);
int _get_naked_pair_count (_self_t self);
int _get_hidden_pair_count (_self_t self);
int _get_pointing_pair_triple_count (_self_t self);
int _get_box_line_reduction_count (_self_t self);
int _get_guess_count (_self_t self);
int _get_backtrack_count (_self_t self);
void _set_print_style (_self_t self, print_style_t ps);
void _set_record_history (_self_t self, bool rec_hist);
void _set_log_history (_self_t self, bool log_hist);
void _print_solve_instructions (_self_t self);
void _print_solve_history (_self_t self);
bool _generate_puzzle_symmetry (_self_t self, symmetry_t symmetry);
bool reset (_self_t self);
bool single_solve_move (_self_t self, int round);
bool only_possibility_for_cell (_self_t self, int round);
bool only_value_in_row (_self_t self, int round);
bool only_value_in_column (_self_t self, int round);
bool only_value_in_section (_self_t self, int round);
int _get_given_count(_self_t self);
bool solve (self_t self);
bool _solve (_self_t);
bool __solve (_self_t, int round);
bool _has_unique_solution (_self_t self);
int _count_solutions (_self_t self, bool limited);
int __count_solutions (_self_t self, int round, bool limited);
bool _is_solved(_self_t self);
bool guess (_self_t self, int round, int guess_number);
bool is_impossible (_self_t self);
void _print_puzzle (_self_t self);
void _print_solution (_self_t self);
void rollback_round (_self_t self, int round);
bool pointing_row_reduction (_self_t self, int round);
bool row_box_reduction (_self_t self, int round);
bool col_box_reduction (_self_t self, int round);
bool pointing_column_reduction (_self_t self, int round);
bool hidden_pair_in_row (_self_t self, int round);
bool hidden_pair_in_column (_self_t self, int round);
bool hidden_pair_in_section (_self_t self, int round);
void mark (_self_t self, int position, int round, int value);
int find_position_with_fewest_possibilities (_self_t self);
bool handle_naked_pairs (_self_t self, int round);
int count_possibilities (_self_t self, int position);
bool are_possibilities_same (_self_t self, int pos_1, int pos_2);
void add_history_item (_self_t self, log_item_t *restrict item);
void shuffle_random_arrays (_self_t self);
void print (_self_t self, const int *const restrict sudoku);
void rollback_non_guesses (_self_t self);
void clear_puzzle (_self_t self);
void print_history (_self_t self, log_list_t *hist);
bool remove_possibilities_in_one_from_two (_self_t self, int pos_1, int pos_2,
                                           int round);
log_list_t *new_log_list (void);
void push (log_list_t *const restrict self, log_item_t *const restrict item);
log_item_t pop (log_list_t *const restrict list);
log_item_t *at (const log_list_t *const restrict list, size_t idx);

char *
get_version ()
{
  return VERSION;
}

typedef struct log_item_t
{
  /**
   * The recursion level at which this item was gathered.
   * Used for backing out log items solve branches that
   * don't lead to a solution.
   */
  int round;

  /**
   * The type of log message that will determine the
   * message printed.
   */
  log_type_t type;

  /**
   * Value that was set by the operation ( or zero for no value )
   */
  int value;

  /**
   * position on the board at which the value ( if any ) was set.
   */
  int position;

  /* methods */
  int (*get_round) (const log_item_t *const);
  log_type_t (*get_type) (const log_item_t *const);
  void (*print) (const struct log_item_t *const);
} log_item_t;

void shuffle_array (int *array, int size);
symmetry_t get_random_symmetry ();
int get_log_count (const log_list_t *const restrict logs, log_type_t type);
static inline int cell_to_column (int cell);
static inline int cell_to_row (int cell);
static inline int cell_to_section_start_cell (int cell);
static inline int cell_to_section (int cell);
static inline int row_to_first_cell (int row);
static inline int column_to_first_cell (int column);
static inline int section_to_first_cell (int section);
static inline int get_possibility_index (int value_index, int cell);
static inline int row_column_to_cell (int row, int column);
static inline int section_to_cell (int section, int offset);

log_list_t *
new_log_list (void)
{
  log_list_t *list = (log_list_t *)malloc (sizeof (log_list_t));

  if (list == NULL)
    {
      fprintf (stderr, "%s\n",
               "Error: could not allocate memory for `log_list_t` object");
      exit (3);
    }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  list->push = push;
  list->pop = pop;
  list->at = at;

  return list;
}

/**
 * Create a new Sudoku board
 */
struct sudoku_board_t *
new_sudoku_board (void)
{
  struct _sudoku_board_t *board
      = (struct _sudoku_board_t *)malloc (sizeof (struct _sudoku_board_t));

  board->puzzle = (int *)malloc (sizeof (int) * BOARD_SIZE);
  *(board->puzzle + 4) = 6;
  board->solution = (int *)malloc (sizeof (int) * BOARD_SIZE);
  board->solution_round = (int *)malloc (sizeof (int) * BOARD_SIZE);
  board->possibilities = (int *)malloc (sizeof (int) * POSSIBILITY_SIZE);
  board->random_board_array = (int *)malloc (sizeof (int) * BOARD_SIZE);
  board->random_possibility_array
      = (int *)malloc (sizeof (int) * ROW_COL_SEC_SIZE);

  board->record_history = false;
  board->log_history = false;
  board->solve_history = new_log_list ();
  board->solve_instructions = new_log_list ();
  board->print_style = READABLE;

  for (int i = 0; i < BOARD_SIZE; i++)
    {
      board->random_board_array[i] = i;
    }
  for (int i = 0; i < ROW_COL_SEC_SIZE; i++)
    {
      board->random_possibility_array[i] = i;
    }

  board->last_solve_round = 0;

  board->set_puzzle = set_puzzle;
  board->get_puzzle = get_puzzle;
  board->get_solution = get_solution;
  board->print_puzzle = print_puzzle;
  board->print_solution = print_solution;
  board->solve = solve;
  board->count_solutions = count_solutions;
  board->has_unique_solution = has_unique_solution;
  board->is_solved = is_solved;
  board->print_solve_history = print_solve_history;
  board->set_record_history = set_record_history;
  board->set_log_history = set_log_history;
  board->set_print_style = set_print_style;
  board->generate_puzzle_symmetry = generate_puzzle_symmetry;
  board->get_given_count = get_given_count;
  board->get_single_count = get_single_count;
  board->get_hidden_single_count = get_hidden_single_count;
  board->get_naked_pair_count = get_naked_pair_count;
  board->get_hidden_pair_count = get_hidden_pair_count;
  board->get_box_line_reduction_count = get_box_line_reduction_count;
  board->get_pointing_pair_triple_count = get_pointing_pair_triple_count;
  board->get_guess_count = get_guess_count;
  board->get_backtrack_count = get_backtrack_count;
  board->print_solve_instructions = print_solve_instructions;
  board->get_difficulty = get_difficulty;
  board->get_difficulty_as_string = get_difficulty_as_string;

  board->reset = reset;
  board->single_solve_move = single_solve_move;
  board->only_possibility_for_cell = only_possibility_for_cell;
  board->only_value_in_row = only_value_in_row;
  board->only_value_in_column = only_value_in_column;
  board->only_value_in_section = only_value_in_section;
  board->solve = solve;
  board->count_solutions = count_solutions;
  board->guess = guess;
  board->is_impossible = is_impossible;
  board->rollback_round = rollback_round;
  board->pointing_row_reduction = pointing_row_reduction;
  board->row_box_reduction = row_box_reduction;
  board->col_box_reduction = col_box_reduction;
  board->pointing_column_reduction = pointing_column_reduction;
  board->hidden_pair_in_row = hidden_pair_in_row;
  board->hidden_pair_in_column = hidden_pair_in_column;
  board->hidden_pair_in_section = hidden_pair_in_section;
  board->mark = mark;
  board->find_position_with_fewest_possibilities
      = find_position_with_fewest_possibilities;
  board->handle_naked_pairs = handle_naked_pairs;
  board->count_possibilities = count_possibilities;
  board->are_possibilities_same = are_possibilities_same;
  board->add_history_item = add_history_item;
  board->shuffle_random_arrays = shuffle_random_arrays;
  board->print = print;
  board->rollback_non_guesses = rollback_non_guesses;
  board->clear_puzzle = clear_puzzle;
  board->print_history = print_history;
  board->remove_possibilities_in_one_from_two
      = remove_possibilities_in_one_from_two;

  sudoku_board_t* tmp = (sudoku_board_t *)board;
  return (sudoku_board_t *)board;
}

/**
 * Get the number of cells that are
 * set in the puzzle (as opposed to
 * figured out in the solution
 */
int
get_given_count (self_t self)
{
  return _get_given_count((_self_t)self);
}

int
_get_given_count (_self_t self)
{
  int count = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      if (self->puzzle[i] != 0)
        count++;
    }
  return count;
}

/**
 * Set the board to the given puzzle.
 * The given puzzle must be an array of 81 integers.
 */
bool
set_puzzle (self_t self, int *init_puzzle)
{
  return _set_puzzle( (_self_t)self, init_puzzle );
}

bool
_set_puzzle (_self_t self, int *init_puzzle)
{
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      self->puzzle[i] = (init_puzzle == NULL) ? 0 : init_puzzle[i];
    }
  return reset (self);
}

/**
 * Retrieves the puzzle as an unmodifiable array of 81 integers.
 */
const int *
get_puzzle (self_t self)
{
  return _get_puzzle( (_self_t)self );
}

const int *
_get_puzzle (_self_t self)
{
  return self->puzzle;
}

/**
 * Retrieves the puzzle's solution as an unmodifiable array of 81 integers.
 */
const int *
get_solution (self_t self)
{
  return _get_solution( (_self_t)self );
}

const int *
_get_solution (_self_t self)
{
  return self->solution;
}

/**
 * Reset the board to its initial state with
 * only the givens.
 * This method clears any solution, resets statistics,
 * and clears any history messages.
 */
bool
reset (_self_t self)
{
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      self->solution[i] = 0;
    }
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      self->solution_round[i] = 0;
    }
  for (int i = 0; i < POSSIBILITY_SIZE; i++)
    {
      self->possibilities[i] = 0;
    }

  log_list_node_t *tail = self->solve_history->tail;
  while (tail != NULL)
    {
      free (tail->next);
    }
  free (self->solve_history);
  free (self->solve_instructions);

  self->solve_history = (log_list_t*)malloc(sizeof(log_list_node_t));
  self->solve_instructions = (log_list_t*)malloc(sizeof(log_list_node_t));

  int round = 1;
  for (int position = 0; position < BOARD_SIZE; position++)
    {
      if (self->puzzle[position] > 0)
        {
          int val_idx = self->puzzle[position] - 1;
          int val_pos = get_possibility_index (val_idx, position);
          int value = self->puzzle[position];
          if (self->possibilities[val_pos] != 0)
            return false;
          mark (self, position, round, value);
          if (self->log_history || self->record_history)
            add_history_item (self,
                              new_val_pos_log (round, GIVEN, value, position));
        }
    }
  return true;
}

/**
 * Get the difficulty rating.
 */
difficulty_t
get_difficulty (self_t self)
{
  if (get_guess_count (self) > 0)
    return EXPERT;
  if (get_box_line_reduction_count (self) > 0)
    return INTERMEDIATE;
  if (get_pointing_pair_triple_count (self) > 0)
    return INTERMEDIATE;
  if (get_hidden_pair_count (self) > 0)
    return INTERMEDIATE;
  if (get_naked_pair_count (self) > 0)
    return INTERMEDIATE;
  if (get_hidden_single_count (self) > 0)
    return EASY;
  if (get_single_count (self) > 0)
    return SIMPLE;
  return UNKNOWN;
}

/**
 * Get the difficulty rating.
 */
char *
get_difficulty_as_string (self_t self)
{
  difficulty_t difficulty = get_difficulty (self);
  switch (difficulty)
    {
    case EXPERT:
      return "Expert";
    case INTERMEDIATE:
      return "Intermediate";
    case EASY:
      return "Easy";
    case SIMPLE:
      return "Simple";
    default:
      return "Unknown";
    }
}

/**
 * Get the number of cells for which the solution was determined
 * because there was only one possible value for that cell.
 */
int
get_single_count (self_t self)
{
  return _get_single_count( (_self_t)self );
}

int
_get_single_count (_self_t self)
{
  return get_log_count (self->solve_instructions, SINGLE);
}

/**
 * Get the number of cells for which the solution was determined
 * because that cell had the only possibility for some value in
 * the row, column, or section.
 */
int
get_hidden_single_count (self_t self)
{
  return _get_hidden_single_count( (_self_t)self );
}

int
_get_hidden_single_count (_self_t self)
{
  return get_log_count (self->solve_instructions, HIDDEN_SINGLE_ROW)
         + get_log_count (self->solve_instructions, HIDDEN_SINGLE_COLUMN)
         + get_log_count (self->solve_instructions, HIDDEN_SINGLE_SECTION);
}

/**
 * Get the number of naked pair reductions that were performed
 * in solving this puzzle.
 */
int
get_naked_pair_count (self_t self)
{
  return _get_naked_pair_count( (_self_t)self );
}

int
_get_naked_pair_count (_self_t self)
{
  return get_log_count (self->solve_instructions, NAKED_PAIR_ROW)
         + get_log_count (self->solve_instructions, NAKED_PAIR_COLUMN)
         + get_log_count (self->solve_instructions, NAKED_PAIR_SECTION);
}

/**
 * Get the number of hidden pair reductions that were performed
 * in solving this puzzle.
 */
int
get_hidden_pair_count (self_t self)
{
  return _get_hidden_pair_count( (_self_t)self );
}

int
_get_hidden_pair_count (_self_t self)
{
  return get_log_count (self->solve_instructions, HIDDEN_PAIR_ROW)
         + get_log_count (self->solve_instructions, HIDDEN_PAIR_COLUMN)
         + get_log_count (self->solve_instructions, HIDDEN_PAIR_SECTION);
}

/**
 * Get the number of pointing pair / triple reductions that were performed
 * in solving this puzzle.
 */
int
get_pointing_pair_triple_count (self_t self)
{
  return _get_pointing_pair_triple_count( (_self_t)self );
}

int
_get_pointing_pair_triple_count (_self_t self)
{
  return get_log_count (self->solve_instructions, POINTING_PAIR_TRIPLE_ROW)
         + get_log_count (self->solve_instructions,
                          POINTING_PAIR_TRIPLE_COLUMN);
}

/**
 * Get the number of box / line reductions that were performed
 * in solving this puzzle.
 */
int
get_box_line_reduction_count (self_t self)
{
  return _get_box_line_reduction_count( (_self_t)self );
}

int
_get_box_line_reduction_count (_self_t self)
{
  return get_log_count (self->solve_instructions, ROW_BOX)
         + get_log_count (self->solve_instructions, COLUMN_BOX);
}

/**
 * Get the number lucky guesses in solving this puzzle.
 */
int
get_guess_count (self_t self)
{
  return _get_guess_count( (_self_t)self );
}

int
_get_guess_count (_self_t self)
{
  return get_log_count (self->solve_instructions, GUESS);
}

/**
 * Get the number of backtracks ( unlucky guesses ) required
 * when solving this puzzle.
 */
int
get_backtrack_count (self_t self)
{
  return _get_backtrack_count( (_self_t)self );
}

int
_get_backtrack_count (_self_t self)
{
  return get_log_count (self->solve_history, ROLLBACK);
}

void
shuffle_random_arrays (_self_t self)
{
  shuffle_array (self->random_board_array, BOARD_SIZE);
  shuffle_array (self->random_possibility_array, ROW_COL_SEC_SIZE);
}

void
clear_puzzle (_self_t self)
{
  // Clear any existing puzzle
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      self->puzzle[i] = 0;
    }
  self->reset (self);
}

bool
generate_puzzle_symmetry (self_t self, symmetry_t symmetry)
{
  return _generate_puzzle_symmetry( (_self_t)self, symmetry );
}

bool
_generate_puzzle_symmetry (_self_t self, symmetry_t symmetry)
{
  if (symmetry == SYMMETRY_RANDOM)
    symmetry = get_random_symmetry ();

  // Don't record history while generating.
  bool rec_hist = self->record_history;
  set_record_history ((self_t)self, false);
  bool log_hist = self->log_history;
  set_log_history ((self_t)self, false);

  self->clear_puzzle (self);

  // Start by getting the randomness in order so that
  // each puzzle will be different from the last.
  self->shuffle_random_arrays (self);

  // Now solve the puzzle the whole way.  The solve
  // uses random algorithms, so we should have a
  // really randomly totally filled sudoku
  // Even when starting from an empty grid
  self->solve ((self_t)self);

  if (symmetry == SYMMETRY_NONE)
    {
      // Rollback any square for which it is obvious that
      // the square doesn't contribute to a unique solution
      // (ie, squares that were filled by logic rather
      // than by guess )
      rollback_non_guesses (self);
    }

  // Record all marked squares as the puzzle so
  // that we can call count_solutions without losing it.
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      self->puzzle[i] = self->solution[i];
    }

  // Rerandomize everything so that we test squares
  // in a different order than they were added.
  self->shuffle_random_arrays (self);

  // Remove one value at a time and see if
  // the puzzle still has only one solution.
  // If it does, leave it out the point because
  // it is not needed.
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      // check all the positions, but in shuffled order
      int position = self->random_board_array[i];
      if (self->puzzle[position] > 0)
        {
          int pos_sym_1 = -1;
          int pos_sym_2 = -1;
          int pos_sym_3 = -1;
          switch (symmetry)
            {
            case SYMMETRY_ROTATE90:
              pos_sym_2 = row_column_to_cell (ROW_COL_SEC_SIZE - 1
                                                  - cell_to_column (position),
                                              cell_to_row (position));
              pos_sym_3 = row_column_to_cell (cell_to_column (position),
                                              ROW_COL_SEC_SIZE - 1
                                                  - cell_to_row (position));
            case SYMMETRY_ROTATE180:
              pos_sym_1 = row_column_to_cell (
                  ROW_COL_SEC_SIZE - 1 - cell_to_row (position),
                  ROW_COL_SEC_SIZE - 1 - cell_to_column (position));
              break;
            case SYMMETRY_MIRROR:
              pos_sym_1 = row_column_to_cell (cell_to_row (position),
                                              ROW_COL_SEC_SIZE - 1
                                                  - cell_to_column (position));
              break;
            case SYMMETRY_FLIP:
              pos_sym_1 = row_column_to_cell (ROW_COL_SEC_SIZE - 1
                                                  - cell_to_row (position),
                                              cell_to_column (position));
              break;
            case SYMMETRY_RANDOM: // NOTE: Should never happen
              break;
            case SYMMETRY_NONE: // NOTE: No need to do anything
              break;
            }
          // try backing out the value and
          // counting solutions to the puzzle
          int saved_value = self->puzzle[position];
          self->puzzle[position] = 0;
          int saved_sym_1 = 0;
          if (pos_sym_1 >= 0)
            {
              saved_sym_1 = self->puzzle[pos_sym_1];
              self->puzzle[pos_sym_1] = 0;
            }
          int saved_sym_2 = 0;
          if (pos_sym_2 >= 0)
            {
              saved_sym_2 = self->puzzle[pos_sym_2];
              self->puzzle[pos_sym_2] = 0;
            }
          int saved_sym_3 = 0;
          if (pos_sym_3 >= 0)
            {
              saved_sym_3 = self->puzzle[pos_sym_3];
              self->puzzle[pos_sym_3] = 0;
            }
          reset (self);
          if (__count_solutions (self, 2, true) > 1)
            {
              // Put it back in, it is needed
              self->puzzle[position] = saved_value;
              if (pos_sym_1 >= 0 && saved_sym_1 != 0)
                self->puzzle[pos_sym_1] = saved_sym_1;
              if (pos_sym_2 >= 0 && saved_sym_2 != 0)
                self->puzzle[pos_sym_2] = saved_sym_2;
              if (pos_sym_3 >= 0 && saved_sym_3 != 0)
                self->puzzle[pos_sym_3] = saved_sym_3;
            }
        }
    }

  // Clear all solution info, leaving just the puzzle.
  reset (self);

  // Restore recording history.
  set_record_history ((self_t)self, rec_hist);
  set_log_history ((self_t)self, log_hist);

  return true;
}

void
rollback_non_guesses (_self_t self)
{
  // Guesses are odd rounds
  // Non-guesses are even rounds
  for (int i = 2; i <= self->last_solve_round; i += 2)
    {
      rollback_round (self, i);
    }
}

void
set_print_style (self_t self, print_style_t ps)
{
  return _set_print_style( (_self_t)self, ps );
}

void
_set_print_style (_self_t self, print_style_t ps)
{
  self->print_style = ps;
}

void
set_record_history (self_t self, bool rec_hist)
{
  return _set_record_history( (_self_t)self, rec_hist );
}

void
_set_record_history (_self_t self, bool rec_hist)
{
  self->record_history = rec_hist;
}

void
set_log_history (self_t self, bool log_hist)
{
  return _set_log_history( (_self_t)self, log_hist );
}

void
_set_log_history (_self_t self, bool log_hist)
{
  self->log_history = log_hist;
}

void
add_history_item (_self_t self, log_item_t *restrict l)
{
  if (self->log_history)
    {
      l->print (l);
      puts ("");
    }
  if (self->record_history)
    {
      self->solve_history->push (self->solve_history, l);
      self->solve_instructions->push (self->solve_history, l);
    }
  else
    {
      free (l);
    }
}

void
print_history (_self_t self, log_list_t *list)
{
  if (!self->record_history)
    {
      fprintf (stdout, "%s", "History was not recorded.");
      if (self->print_style == CSV)
        {
          fprintf (stdout, "%s", " -- ");
        }
      else
        {
          puts ("");
        }
    }

  log_list_node_t *head = list->head;
  for (unsigned int i = 0; i < list->size; i++)
    {
      fprintf (stdout, "%d%s", i + 1, ". ");
      head->item->print (head->item);
      if (self->print_style == CSV)
        {
          fprintf (stdout, "%s", " -- ");
        }
      else
        {
          puts ("");
        }
    }
  if (self->print_style == CSV)
    {
      fprintf (stdout, "%s", ",");
    }
  else
    {
      puts ("");
    }
}

void
print_solve_instructions (self_t self)
{
  return _print_solve_instructions( (_self_t)self );
}

void
_print_solve_instructions (_self_t self)
{
  if (is_solved ((self_t)self))
    {
      print_history (self, self->solve_instructions);
    }
  else
    {
      fprintf (stdout, "%s\n",
               "No solve instructions - Puzzle is not possible to solve.");
    }
}

void
print_solve_history (self_t self)
{
  return _print_solve_history( (_self_t)self );
}

void
_print_solve_history (_self_t self)
{
  print_history (self, self->solve_history);
}

bool
solve (self_t self)
{
  return _solve( (_self_t)self );
}

bool
_solve (_self_t self)
{
  reset (self);
  shuffle_random_arrays (self);
  return __solve (self, 2);
}

bool
__solve (_self_t self, int round)
{
  self->last_solve_round = round;

  while (single_solve_move (self, round))
    {
      if (is_solved ((self_t)self))
        return true;
      if (is_impossible (self))
        return false;
    }

  int next_guess_round = round + 1;
  int next_round = round + 2;
  for (int guess_number = 0; guess (self, next_guess_round, guess_number);
       guess_number++)
    {
      if (is_impossible (self) || !__solve (self, next_round))
        {
          rollback_round (self, next_round);
          rollback_round (self, next_guess_round);
        }
      else
        {
          return true;
        }
    }
  return false;
}

bool
has_unique_solution (self_t self)
{
  return _has_unique_solution( (_self_t)self );
}

bool
_has_unique_solution (_self_t self)
{
  return count_solutions ((self_t)self, true) == 1;
}

int
count_solutions (self_t self, bool limit_to_two)
{
  return _count_solutions( (_self_t)self, limit_to_two );
}

int
_count_solutions (_self_t self, bool limit_to_two)
{
  // Don't record history while generating.
  bool rec_hist = self->record_history;
  set_record_history ((self_t)self, false);
  bool log_hist = self->log_history;
  set_log_history ((self_t)self, false);

  reset (self);
  int solution_count = __count_solutions (self, 2, limit_to_two);

  // Restore recording history.
  set_record_history ((self_t)self, rec_hist);
  set_log_history ((self_t)self, log_hist);

  return solution_count;
}

int
__count_solutions (_self_t self, int round, bool limit_to_two)
{
  while (single_solve_move (self, round))
    {
      if (is_solved ((self_t)self))
        {
          rollback_round (self, round);
          return 1;
        }
      if (is_impossible (self))
        {
          rollback_round (self, round);
          return 0;
        }
    }

  int solutions = 0;
  int next_round = round + 1;
  for (int guess_number = 0; guess (self, next_round, guess_number);
       guess_number++)
    {
      solutions += __count_solutions (self, next_round, limit_to_two);
      if (limit_to_two && solutions >= 2)
        {
          rollback_round (self, round);
          return solutions;
        }
    }
  rollback_round (self, round);
  return solutions;
}

void
rollback_round (_self_t self, int round)
{
  if (self->log_history || self->record_history)
    add_history_item (self, new_std_log (round, ROLLBACK));
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      if (self->solution_round[i] == round)
        {
          self->solution_round[i] = 0;
          self->solution[i] = 0;
        }
    }
  for (int i = 0; i < POSSIBILITY_SIZE; i++)
    {
      if (self->possibilities[i] == round)
        {
          self->possibilities[i] = 0;
        }
    }

  log_list_t *s_ins = self->solve_instructions;
  while (s_ins->size > 0
         && s_ins->tail->item->get_round (s_ins->tail->item) == round)
    {
      self->solve_instructions->pop (self->solve_instructions);
    }
}

bool
is_solved (self_t self)
{
  return _is_solved( (_self_t)self );
}

bool
_is_solved (_self_t self)
{
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      if (self->solution[i] == 0)
        {
          return false;
        }
    }
  return true;
}

bool
is_impossible (_self_t self)
{
  for (int position = 0; position < BOARD_SIZE; position++)
    {
      if (self->solution[position] == 0)
        {
          int count = 0;
          for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
            {
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                count++;
            }
          if (count == 0)
            {
              return true;
            }
        }
    }
  return false;
}

int
find_position_with_fewest_possibilities (_self_t self)
{
  int min_possibilities = 10;
  int best_position = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      int position = self->random_board_array[i];
      if (self->solution[position] == 0)
        {
          int count = 0;
          for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
            {
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                count++;
            }
          if (count < min_possibilities)
            {
              min_possibilities = count;
              best_position = position;
            }
        }
    }
  return best_position;
}

bool
guess (_self_t self, int round, int guess_number)
{
  int local_guess_count = 0;
  int position = find_position_with_fewest_possibilities (self);
  for (int i = 0; i < ROW_COL_SEC_SIZE; i++)
    {
      int val_idx = self->random_possibility_array[i];
      int val_pos = get_possibility_index (val_idx, position);
      if (self->possibilities[val_pos] == 0)
        {
          if (local_guess_count == guess_number)
            {
              int value = val_idx + 1;
              if (self->log_history || self->record_history)
                add_history_item (
                    self, new_val_pos_log (round, GUESS, value, position));
              mark (self, position, round, value);
              return true;
            }
          local_guess_count++;
        }
    }
  return false;
}

bool
single_solve_move (_self_t self, int round)
{
  if (only_possibility_for_cell (self, round))
    return true;
  if (only_value_in_section (self, round))
    return true;
  if (only_value_in_row (self, round))
    return true;
  if (only_value_in_column (self, round))
    return true;
  if (handle_naked_pairs (self, round))
    return true;
  if (pointing_row_reduction (self, round))
    return true;
  if (pointing_column_reduction (self, round))
    return true;
  if (row_box_reduction (self, round))
    return true;
  if (col_box_reduction (self, round))
    return true;
  if (hidden_pair_in_row (self, round))
    return true;
  if (hidden_pair_in_column (self, round))
    return true;
  if (hidden_pair_in_section (self, round))
    return true;
  return false;
}

bool
col_box_reduction (_self_t self, int round)
{
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      for (int col = 0; col < ROW_COL_SEC_SIZE; col++)
        {
          int col_start = column_to_first_cell (col);
          bool in_one_box = true;
          int col_box = -1;
          for (int i = 0; i < GRID_SIZE; i++)
            {
              for (int j = 0; j < GRID_SIZE; j++)
                {
                  int row = i * GRID_SIZE + j;
                  int position = row_column_to_cell (row, col);
                  int val_pos = get_possibility_index (val_idx, position);
                  if (self->possibilities[val_pos] == 0)
                    {
                      if (col_box == -1 || col_box == i)
                        {
                          col_box = i;
                        }
                      else
                        {
                          in_one_box = false;
                        }
                    }
                }
            }
          if (in_one_box && col_box != -1)
            {
              bool done_something = false;
              int row = GRID_SIZE * col_box;
              int sec_start
                  = cell_to_section_start_cell (row_column_to_cell (row, col));
              int sec_start_row = cell_to_row (sec_start);
              int sec_start_col = cell_to_column (sec_start);
              for (int i = 0; i < GRID_SIZE; i++)
                {
                  for (int j = 0; j < GRID_SIZE; j++)
                    {
                      int row2 = sec_start_row + i;
                      int col2 = sec_start_col + j;
                      int position = row_column_to_cell (row2, col2);
                      int val_pos = get_possibility_index (val_idx, position);
                      if (col != col2 && self->possibilities[val_pos] == 0)
                        {
                          self->possibilities[val_pos] = round;
                          done_something = true;
                        }
                    }
                }
              if (done_something)
                {
                  if (self->log_history || self->record_history)
                    add_history_item (self, new_val_pos_log (round, COLUMN_BOX,
                                                             val_idx + 1,
                                                             col_start));
                  return true;
                }
            }
        }
    }
  return false;
}

bool
row_box_reduction (_self_t self, int round)
{
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      for (int row = 0; row < ROW_COL_SEC_SIZE; row++)
        {
          int row_start = row_to_first_cell (row);
          bool in_one_box = true;
          int row_box = -1;
          for (int i = 0; i < GRID_SIZE; i++)
            {
              for (int j = 0; j < GRID_SIZE; j++)
                {
                  int column = i * GRID_SIZE + j;
                  int position = row_column_to_cell (row, column);
                  int val_pos = get_possibility_index (val_idx, position);
                  if (self->possibilities[val_pos] == 0)
                    {
                      if (row_box == -1 || row_box == i)
                        {
                          row_box = i;
                        }
                      else
                        {
                          in_one_box = false;
                        }
                    }
                }
            }
          if (in_one_box && row_box != -1)
            {
              bool done_something = false;
              int column = GRID_SIZE * row_box;
              int sec_start = cell_to_section_start_cell (
                  row_column_to_cell (row, column));
              int sec_start_row = cell_to_row (sec_start);
              int sec_start_col = cell_to_column (sec_start);
              for (int i = 0; i < GRID_SIZE; i++)
                {
                  for (int j = 0; j < GRID_SIZE; j++)
                    {
                      int row2 = sec_start_row + i;
                      int col2 = sec_start_col + j;
                      int position = row_column_to_cell (row2, col2);
                      int val_pos = get_possibility_index (val_idx, position);
                      if (row != row2 && self->possibilities[val_pos] == 0)
                        {
                          self->possibilities[val_pos] = round;
                          done_something = true;
                        }
                    }
                }
              if (done_something)
                {
                  if (self->log_history || self->record_history)
                    add_history_item (self, new_val_pos_log (round, ROW_BOX,
                                                             val_idx + 1,
                                                             row_start));
                  return true;
                }
            }
        }
    }
  return false;
}

bool
pointing_row_reduction (_self_t self, int round)
{
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      for (int section = 0; section < ROW_COL_SEC_SIZE; section++)
        {
          int sec_start = section_to_first_cell (section);
          bool in_one_row = true;
          int box_row = -1;
          for (int j = 0; j < GRID_SIZE; j++)
            {
              for (int i = 0; i < GRID_SIZE; i++)
                {
                  int sec_val = sec_start + i + (ROW_COL_SEC_SIZE * j);
                  int val_pos = get_possibility_index (val_idx, sec_val);
                  if (self->possibilities[val_pos] == 0)
                    {
                      if (box_row == -1 || box_row == j)
                        {
                          box_row = j;
                        }
                      else
                        {
                          in_one_row = false;
                        }
                    }
                }
            }
          if (in_one_row && box_row != -1)
            {
              bool done_something = false;
              int row = cell_to_row (sec_start) + box_row;
              int row_start = row_to_first_cell (row);

              for (int i = 0; i < ROW_COL_SEC_SIZE; i++)
                {
                  int position = row_start + i;
                  int section2 = cell_to_section (position);
                  int val_pos = get_possibility_index (val_idx, position);
                  if (section != section2 && self->possibilities[val_pos] == 0)
                    {
                      self->possibilities[val_pos] = round;
                      done_something = true;
                    }
                }
              if (done_something)
                {
                  if (self->log_history || self->record_history)
                    add_history_item (
                        self, new_val_pos_log (round, POINTING_PAIR_TRIPLE_ROW,
                                               val_idx + 1, row_start));
                  return true;
                }
            }
        }
    }
  return false;
}

bool
pointing_column_reduction (_self_t self, int round)
{
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      for (int section = 0; section < ROW_COL_SEC_SIZE; section++)
        {
          int sec_start = section_to_first_cell (section);
          bool in_one_col = true;
          int box_col = -1;
          for (int i = 0; i < GRID_SIZE; i++)
            {
              for (int j = 0; j < GRID_SIZE; j++)
                {
                  int sec_val = sec_start + i + (ROW_COL_SEC_SIZE * j);
                  int val_pos = get_possibility_index (val_idx, sec_val);
                  if (self->possibilities[val_pos] == 0)
                    {
                      if (box_col == -1 || box_col == i)
                        {
                          box_col = i;
                        }
                      else
                        {
                          in_one_col = false;
                        }
                    }
                }
            }
          if (in_one_col && box_col != -1)
            {
              bool done_something = false;
              int col = cell_to_column (sec_start) + box_col;
              int col_start = column_to_first_cell (col);

              for (int i = 0; i < ROW_COL_SEC_SIZE; i++)
                {
                  int position = col_start + (ROW_COL_SEC_SIZE * i);
                  int section2 = cell_to_section (position);
                  int val_pos = get_possibility_index (val_idx, position);
                  if (section != section2 && self->possibilities[val_pos] == 0)
                    {
                      self->possibilities[val_pos] = round;
                      done_something = true;
                    }
                }
              if (done_something)
                {
                  if (self->log_history || self->record_history)
                    add_history_item (
                        self,
                        new_val_pos_log (round, POINTING_PAIR_TRIPLE_COLUMN,
                                         val_idx + 1, col_start));
                  return true;
                }
            }
        }
    }
  return false;
}

int
count_possibilities (_self_t self, int position)
{
  int count = 0;
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      int val_pos = get_possibility_index (val_idx, position);
      if (self->possibilities[val_pos] == 0)
        count++;
    }
  return count;
}

bool
are_possibilities_same (_self_t self, int position1, int position2)
{
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      int val_pos1 = get_possibility_index (val_idx, position1);
      int val_pos2 = get_possibility_index (val_idx, position2);
      if ((self->possibilities[val_pos1] == 0
           || self->possibilities[val_pos2] == 0)
          && (self->possibilities[val_pos1] != 0
              || self->possibilities[val_pos2] != 0))
        {
          return false;
        }
    }
  return true;
}

bool
remove_possibilities_in_one_from_two (_self_t self, int position1,
                                      int position2, int round)
{
  bool done_something = false;
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      int val_pos1 = get_possibility_index (val_idx, position1);
      int val_pos2 = get_possibility_index (val_idx, position2);
      if (self->possibilities[val_pos1] == 0
          && self->possibilities[val_pos2] == 0)
        {
          self->possibilities[val_pos2] = round;
          done_something = true;
        }
    }
  return done_something;
}

bool
hidden_pair_in_column (_self_t self, int round)
{
  for (int column = 0; column < ROW_COL_SEC_SIZE; column++)
    {
      for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
        {
          int r1 = -1;
          int r2 = -1;
          int val_count = 0;
          for (int row = 0; row < ROW_COL_SEC_SIZE; row++)
            {
              int position = row_column_to_cell (row, column);
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                {
                  if (r1 == -1 || r1 == row)
                    {
                      r1 = row;
                    }
                  else if (r2 == -1 || r2 == row)
                    {
                      r2 = row;
                    }
                  val_count++;
                }
            }
          if (val_count == 2)
            {
              for (int val_idx2 = val_idx + 1; val_idx2 < ROW_COL_SEC_SIZE;
                   val_idx2++)
                {
                  int r3 = -1;
                  int r4 = -1;
                  int val_count2 = 0;
                  for (int row = 0; row < ROW_COL_SEC_SIZE; row++)
                    {
                      int position = row_column_to_cell (row, column);
                      int val_pos = get_possibility_index (val_idx2, position);
                      if (self->possibilities[val_pos] == 0)
                        {
                          if (r3 == -1 || r3 == row)
                            {
                              r3 = row;
                            }
                          else if (r4 == -1 || r4 == row)
                            {
                              r4 = row;
                            }
                          val_count2++;
                        }
                    }
                  if (val_count2 == 2 && r1 == r3 && r2 == r4)
                    {
                      bool done_something = false;
                      for (int val_idx3 = 0; val_idx3 < ROW_COL_SEC_SIZE;
                           val_idx3++)
                        {
                          if (val_idx3 != val_idx && val_idx3 != val_idx2)
                            {
                              int position1 = row_column_to_cell (r1, column);
                              int position2 = row_column_to_cell (r2, column);
                              int val_pos1 = get_possibility_index (val_idx3,
                                                                    position1);
                              int val_pos2 = get_possibility_index (val_idx3,
                                                                    position2);
                              if (self->possibilities[val_pos1] == 0)
                                {
                                  self->possibilities[val_pos1] = round;
                                  done_something = true;
                                }
                              if (self->possibilities[val_pos2] == 0)
                                {
                                  self->possibilities[val_pos2] = round;
                                  done_something = true;
                                }
                            }
                        }
                      if (done_something)
                        {
                          if (self->log_history || self->record_history)
                            add_history_item (
                                self,
                                new_val_pos_log (
                                    round, HIDDEN_PAIR_COLUMN, val_idx + 1,
                                    row_column_to_cell (r1, column)));
                          return true;
                        }
                    }
                }
            }
        }
    }
  return false;
}

bool
hidden_pair_in_section (_self_t self, int round)
{
  for (int section = 0; section < ROW_COL_SEC_SIZE; section++)
    {
      for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
        {
          int si1 = -1;
          int si2 = -1;
          int val_count = 0;
          for (int sec_ind = 0; sec_ind < ROW_COL_SEC_SIZE; sec_ind++)
            {
              int position = section_to_cell (section, sec_ind);
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                {
                  if (si1 == -1 || si1 == sec_ind)
                    {
                      si1 = sec_ind;
                    }
                  else if (si2 == -1 || si2 == sec_ind)
                    {
                      si2 = sec_ind;
                    }
                  val_count++;
                }
            }
          if (val_count == 2)
            {
              for (int val_idx2 = val_idx + 1; val_idx2 < ROW_COL_SEC_SIZE;
                   val_idx2++)
                {
                  int si3 = -1;
                  int si4 = -1;
                  int val_count2 = 0;
                  for (int sec_ind = 0; sec_ind < ROW_COL_SEC_SIZE; sec_ind++)
                    {
                      int position = section_to_cell (section, sec_ind);
                      int val_pos = get_possibility_index (val_idx2, position);
                      if (self->possibilities[val_pos] == 0)
                        {
                          if (si3 == -1 || si3 == sec_ind)
                            {
                              si3 = sec_ind;
                            }
                          else if (si4 == -1 || si4 == sec_ind)
                            {
                              si4 = sec_ind;
                            }
                          val_count2++;
                        }
                    }
                  if (val_count2 == 2 && si1 == si3 && si2 == si4)
                    {
                      bool done_something = false;
                      for (int val_idx3 = 0; val_idx3 < ROW_COL_SEC_SIZE;
                           val_idx3++)
                        {
                          if (val_idx3 != val_idx && val_idx3 != val_idx2)
                            {
                              int position1 = section_to_cell (section, si1);
                              int position2 = section_to_cell (section, si2);
                              int val_pos1 = get_possibility_index (val_idx3,
                                                                    position1);
                              int val_pos2 = get_possibility_index (val_idx3,
                                                                    position2);
                              if (self->possibilities[val_pos1] == 0)
                                {
                                  self->possibilities[val_pos1] = round;
                                  done_something = true;
                                }
                              if (self->possibilities[val_pos2] == 0)
                                {
                                  self->possibilities[val_pos2] = round;
                                  done_something = true;
                                }
                            }
                        }
                      if (done_something)
                        {
                          if (self->log_history || self->record_history)
                            add_history_item (
                                self,
                                new_val_pos_log (
                                    round, HIDDEN_PAIR_SECTION, val_idx + 1,
                                    section_to_cell (section, si1)));
                          return true;
                        }
                    }
                }
            }
        }
    }
  return false;
}

bool
hidden_pair_in_row (_self_t self, int round)
{
  for (int row = 0; row < ROW_COL_SEC_SIZE; row++)
    {
      for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
        {
          int c1 = -1;
          int c2 = -1;
          int val_count = 0;
          for (int column = 0; column < ROW_COL_SEC_SIZE; column++)
            {
              int position = row_column_to_cell (row, column);
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                {
                  if (c1 == -1 || c1 == column)
                    {
                      c1 = column;
                    }
                  else if (c2 == -1 || c2 == column)
                    {
                      c2 = column;
                    }
                  val_count++;
                }
            }
          if (val_count == 2)
            {
              for (int val_idx2 = val_idx + 1; val_idx2 < ROW_COL_SEC_SIZE;
                   val_idx2++)
                {
                  int c3 = -1;
                  int c4 = -1;
                  int val_count2 = 0;
                  for (int column = 0; column < ROW_COL_SEC_SIZE; column++)
                    {
                      int position = row_column_to_cell (row, column);
                      int val_pos = get_possibility_index (val_idx2, position);
                      if (self->possibilities[val_pos] == 0)
                        {
                          if (c3 == -1 || c3 == column)
                            {
                              c3 = column;
                            }
                          else if (c4 == -1 || c4 == column)
                            {
                              c4 = column;
                            }
                          val_count2++;
                        }
                    }
                  if (val_count2 == 2 && c1 == c3 && c2 == c4)
                    {
                      bool done_something = false;
                      for (int val_idx3 = 0; val_idx3 < ROW_COL_SEC_SIZE;
                           val_idx3++)
                        {
                          if (val_idx3 != val_idx && val_idx3 != val_idx2)
                            {
                              int position1 = row_column_to_cell (row, c1);
                              int position2 = row_column_to_cell (row, c2);
                              int val_pos1 = get_possibility_index (val_idx3,
                                                                    position1);
                              int val_pos2 = get_possibility_index (val_idx3,
                                                                    position2);
                              if (self->possibilities[val_pos1] == 0)
                                {
                                  self->possibilities[val_pos1] = round;
                                  done_something = true;
                                }
                              if (self->possibilities[val_pos2] == 0)
                                {
                                  self->possibilities[val_pos2] = round;
                                  done_something = true;
                                }
                            }
                        }
                      if (done_something)
                        {
                          if (self->log_history || self->record_history)
                            add_history_item (
                                self, new_val_pos_log (
                                          round, HIDDEN_PAIR_ROW, val_idx + 1,
                                          row_column_to_cell (row, c1)));
                          return true;
                        }
                    }
                }
            }
        }
    }
  return false;
}

bool
handle_naked_pairs (_self_t self, int round)
{
  for (int position = 0; position < BOARD_SIZE; position++)
    {
      int possibilities = count_possibilities (self, position);
      if (possibilities == 2)
        {
          int row = cell_to_row (position);
          int column = cell_to_column (position);
          int section = cell_to_section_start_cell (position);
          for (int position2 = position; position2 < BOARD_SIZE; position2++)
            {
              if (position != position2)
                {
                  int possibilities2 = count_possibilities (self, position2);
                  if (possibilities2 == 2
                      && are_possibilities_same (self, position, position2))
                    {
                      if (row == cell_to_row (position2))
                        {
                          bool done_something = false;
                          for (int column2 = 0; column2 < ROW_COL_SEC_SIZE;
                               column2++)
                            {
                              int position3
                                  = row_column_to_cell (row, column2);
                              if (position3 != position
                                  && position3 != position2
                                  && remove_possibilities_in_one_from_two (
                                      self, position, position3, round))
                                {
                                  done_something = true;
                                }
                            }
                          if (done_something)
                            {
                              if (self->log_history || self->record_history)
                                add_history_item (
                                    self,
                                    new_val_pos_log (round, NAKED_PAIR_ROW, 0,
                                                     position));
                              return true;
                            }
                        }
                      if (column == cell_to_column (position2))
                        {
                          bool done_something = false;
                          for (int row2 = 0; row2 < ROW_COL_SEC_SIZE; row2++)
                            {
                              int position3
                                  = row_column_to_cell (row2, column);
                              if (position3 != position
                                  && position3 != position2
                                  && remove_possibilities_in_one_from_two (
                                      self, position, position3, round))
                                {
                                  done_something = true;
                                }
                            }
                          if (done_something)
                            {
                              if (self->log_history || self->record_history)
                                add_history_item (
                                    self,
                                    new_val_pos_log (round, NAKED_PAIR_COLUMN,
                                                     0, position));
                              return true;
                            }
                        }
                      if (section == cell_to_section_start_cell (position2))
                        {
                          bool done_something = false;
                          int sec_start
                              = cell_to_section_start_cell (position);
                          for (int i = 0; i < GRID_SIZE; i++)
                            {
                              for (int j = 0; j < GRID_SIZE; j++)
                                {
                                  int position3
                                      = sec_start + i + (ROW_COL_SEC_SIZE * j);
                                  if (position3 != position
                                      && position3 != position2
                                      && remove_possibilities_in_one_from_two (
                                          self, position, position3, round))
                                    {
                                      done_something = true;
                                    }
                                }
                            }
                          if (done_something)
                            {
                              if (self->log_history || self->record_history)
                                add_history_item (
                                    self,
                                    new_val_pos_log (round, NAKED_PAIR_SECTION,
                                                     0, position));
                              return true;
                            }
                        }
                    }
                }
            }
        }
    }
  return false;
}

/**
 * Mark exactly one cell which is the only possible value for some row, if
 * such a cell exists.
 * This method will look in a row for a possibility that is only listed
 * for one cell.  This type of cell is often called a "hidden single"
 */
bool
only_value_in_row (_self_t self, int round)
{
  for (int row = 0; row < ROW_COL_SEC_SIZE; row++)
    {
      for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
        {
          int count = 0;
          int last_position = 0;
          for (int col = 0; col < ROW_COL_SEC_SIZE; col++)
            {
              int position = (row * ROW_COL_SEC_SIZE) + col;
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                {
                  count++;
                  last_position = position;
                }
            }
          if (count == 1)
            {
              int value = val_idx + 1;
              if (self->log_history || self->record_history)
                add_history_item (self,
                                  new_val_pos_log (round, HIDDEN_SINGLE_ROW,
                                                   value, last_position));
              mark (self, last_position, round, value);
              return true;
            }
        }
    }
  return false;
}

/**
 * Mark exactly one cell which is the only possible value for some column, if
 * such a cell exists.
 * This method will look in a column for a possibility that is only listed
 * for one cell.  This type of cell is often called a "hidden single"
 */
bool
only_value_in_column (_self_t self, int round)
{
  for (int col = 0; col < ROW_COL_SEC_SIZE; col++)
    {
      for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
        {
          int count = 0;
          int last_position = 0;
          for (int row = 0; row < ROW_COL_SEC_SIZE; row++)
            {
              int position = row_column_to_cell (row, col);
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                {
                  count++;
                  last_position = position;
                }
            }
          if (count == 1)
            {
              int value = val_idx + 1;
              if (self->log_history || self->record_history)
                add_history_item (self,
                                  new_val_pos_log (round, HIDDEN_SINGLE_COLUMN,
                                                   value, last_position));
              mark (self, last_position, round, value);
              return true;
            }
        }
    }
  return false;
}

/**
 * Mark exactly one cell which is the only possible value for some section, if
 * such a cell exists.
 * This method will look in a section for a possibility that is only listed
 * for one cell.  This type of cell is often called a "hidden single"
 */
bool
only_value_in_section (_self_t self, int round)
{
  for (int sec = 0; sec < ROW_COL_SEC_SIZE; sec++)
    {
      int sec_pos = section_to_first_cell (sec);
      for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
        {
          int count = 0;
          int last_position = 0;
          for (int i = 0; i < GRID_SIZE; i++)
            {
              for (int j = 0; j < GRID_SIZE; j++)
                {
                  int position = sec_pos + i + ROW_COL_SEC_SIZE * j;
                  int val_pos = get_possibility_index (val_idx, position);
                  if (self->possibilities[val_pos] == 0)
                    {
                      count++;
                      last_position = position;
                    }
                }
            }
          if (count == 1)
            {
              int value = val_idx + 1;
              if (self->log_history || self->record_history)
                add_history_item (
                    self, new_val_pos_log (round, HIDDEN_SINGLE_SECTION, value,
                                           last_position));
              mark (self, last_position, round, value);
              return true;
            }
        }
    }
  return false;
}

bool
only_possibility_for_cell (_self_t self, int round)
{
  for (int position = 0; position < BOARD_SIZE; position++)
    {
      if (self->solution[position] == 0)
        {
          int count = 0;
          int last_value = 0;
          for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
            {
              int val_pos = get_possibility_index (val_idx, position);
              if (self->possibilities[val_pos] == 0)
                {
                  count++;
                  last_value = val_idx + 1;
                }
            }
          if (count == 1)
            {
              mark (self, position, round, last_value);
              if (self->log_history || self->record_history)
                add_history_item (
                    self,
                    new_val_pos_log (round, SINGLE, last_value, position));
              return true;
            }
        }
    }
  return false;
}

/**
 * Mark the given value at the given position.  Go through
 * the row, column, and section for the position and remove
 * the value from the possibilities.
 *
 * @param position Position into the board ( 0-80 )
 * @param round Round to mark for rollback purposes
 * @param value The value to go in the square at the given position
 */
void
mark (_self_t self, int position, int round, int value)
{
  if (self->solution[position] != 0)
    fprintf (stderr, "%s\n", "Marking position that already has been marked.");
  if (self->solution_round[position] != 0)
    fprintf (stderr, "%s\n",
             "Marking position that was marked another round.");
  int val_idx = value - 1;
  self->solution[position] = value;

  int poss_ind = get_possibility_index (val_idx, position);
  if (self->possibilities[poss_ind] != 0)
    fprintf (stderr, "%s\n", "Marking impossible position.");

  // Take this value out of the possibilities for everything in the row
  self->solution_round[position] = round;
  int row_start = cell_to_row (position) * ROW_COL_SEC_SIZE;
  for (int col = 0; col < ROW_COL_SEC_SIZE; col++)
    {
      int row_val = row_start + col;
      int val_pos = get_possibility_index (val_idx, row_val);
      if (self->possibilities[val_pos] == 0)
        {
          self->possibilities[val_pos] = round;
        }
    }

  // Take this value out of the possibilities for everything in the column
  int col_start = cell_to_column (position);
  for (int i = 0; i < ROW_COL_SEC_SIZE; i++)
    {
      int col_val = col_start + (ROW_COL_SEC_SIZE * i);
      int val_pos = get_possibility_index (val_idx, col_val);
      if (self->possibilities[val_pos] == 0)
        {
          self->possibilities[val_pos] = round;
        }
    }

  // Take this value out of the possibilities for everything in section
  int sec_start = cell_to_section_start_cell (position);
  for (int i = 0; i < GRID_SIZE; i++)
    {
      for (int j = 0; j < GRID_SIZE; j++)
        {
          int sec_val = sec_start + i + (ROW_COL_SEC_SIZE * j);
          int val_pos = get_possibility_index (val_idx, sec_val);
          if (self->possibilities[val_pos] == 0)
            {
              self->possibilities[val_pos] = round;
            }
        }
    }

  // This position itself is determined, it should have possibilities.
  for (int val_idx = 0; val_idx < ROW_COL_SEC_SIZE; val_idx++)
    {
      int val_pos = get_possibility_index (val_idx, position);
      if (self->possibilities[val_pos] == 0)
        {
          self->possibilities[val_pos] = round;
        }
    }
}

void
print (_self_t self, const int *const restrict sudoku)
{
  for (int i = 0; i < BOARD_SIZE; i++)
    {
      if (self->print_style == READABLE)
        {
          fprintf (stdout, "%s", " ");
        }
      if (sudoku[i] == 0)
        {
          fprintf (stdout, "%c", '.');
        }
      else
        {
          fprintf (stdout, "%d", sudoku[i]);
        }
      if (i == BOARD_SIZE - 1)
        {
          if (self->print_style == CSV)
            {
              fprintf (stdout, "%s", ",");
            }
          else
            {
              puts ("");
            }
          if (self->print_style == READABLE || self->print_style == COMPACT)
            {
              puts ("");
            }
        }
      else if (i % ROW_COL_SEC_SIZE == ROW_COL_SEC_SIZE - 1)
        {
          if (self->print_style == READABLE || self->print_style == COMPACT)
            {
              puts ("");
            }
          if (i % SEC_GROUP_SIZE == SEC_GROUP_SIZE - 1)
            {
              if (self->print_style == READABLE)
                {
                  fprintf (stdout, "%s\n", "-------|-------|-------");
                }
            }
        }
      else if (i % GRID_SIZE == GRID_SIZE - 1)
        {
          if (self->print_style == READABLE)
            {
              fprintf (stdout, "%s", " |");
            }
        }
    }
}

void
print_puzzle (self_t self)
{
  return _print_puzzle( (_self_t)self );
}

void
_print_puzzle (_self_t self)
{
  print (self, self->puzzle);
}

void
print_solution (self_t self)
{
  return _print_solution( (_self_t)self );
}

void
_print_solution (_self_t self)
{
  print (self, self->solution);
}

log_item_t *
new_std_log (int r, log_type_t t)
{
  log_item_t *item = (log_item_t *)malloc (sizeof (log_item_t));

  if (item == NULL)
    {
      fprintf (stderr, "%s\n",
               "Error: could not allocate memory to `log_item_t` object");
      exit (3);
    }

  item->round = r;
  item->type = t;
  item->value = 0;
  item->position = -1;

  return item;
}

log_item_t *
new_val_pos_log (int r, log_type_t t, int v, int p)
{
  log_item_t *item = (log_item_t *)malloc (sizeof (log_item_t));

  if (item == NULL)
    {
      fprintf (stderr, "%s\n",
               "Error: could not allocate memory to `log_item_t` object");
      exit (3);
    }

  item->round = r;
  item->type = t;
  item->value = v;
  item->position = p;

  return item;
}

int
_get_round (const log_item_t *const restrict self)
{
  return self->round;
}

/**
 * Get the type of this log item.
 */
log_type_t
get_type (const log_item_t *const restrict self)
{
  return self->type;
}

/**
 * Print the current log item.  The message used is
 * determined by the type of log item.
 */
void
_print (const log_item_t *const restrict self)
{
  fprintf (stdout, "%s%d%s", "Round: ", self->get_round (self), " - ");
  switch (self->get_type (self))
    {
    case GIVEN:
      fprintf (stdout, "%s", "Mark given");
      break;
    case ROLLBACK:
      fprintf (stdout, "%s", "Roll back round");
      break;
    case GUESS:
      fprintf (stdout, "%s", "Mark guess (start round )");
      break;
    case HIDDEN_SINGLE_ROW:
      fprintf (stdout, "%s", "Mark single possibility for value in row");
      break;
    case HIDDEN_SINGLE_COLUMN:
      fprintf (stdout, "%s", "Mark single possibility for value in column");
      break;
    case HIDDEN_SINGLE_SECTION:
      fprintf (stdout, "%s", "Mark single possibility for value in section");
      break;
    case SINGLE:
      fprintf (stdout, "%s", "Mark only possibility for cell");
      break;
    case NAKED_PAIR_ROW:
      fprintf (stdout, "%s", "Remove possibilities for naked pair in row");
      break;
    case NAKED_PAIR_COLUMN:
      fprintf (stdout, "%s", "Remove possibilities for naked pair in column");
      break;
    case NAKED_PAIR_SECTION:
      fprintf (stdout, "%s", "Remove possibilities for naked pair in section");
      break;
    case POINTING_PAIR_TRIPLE_ROW:
      fprintf (stdout, "%s",
               "Remove possibilities for row because all values are in one "
               "section");
      break;
    case POINTING_PAIR_TRIPLE_COLUMN:
      fprintf (stdout, "%s",
               "Remove possibilities for column because all values are in one "
               "section");
      break;
    case ROW_BOX:
      fprintf (stdout, "%s",
               "Remove possibilities for section because all values are in "
               "one row");
      break;
    case COLUMN_BOX:
      fprintf (stdout, "%s",
               "Remove possibilities for section because all values are in "
               "one column");
      break;
    case HIDDEN_PAIR_ROW:
      fprintf (stdout, "%s", "Remove possibilities from hidden pair in row");
      break;
    case HIDDEN_PAIR_COLUMN:
      fprintf (stdout, "%s",
               "Remove possibilities from hidden pair in column");
      break;
    case HIDDEN_PAIR_SECTION:
      fprintf (stdout, "%s",
               "Remove possibilities from hidden pair in section");
      break;
    default:
      fprintf (stdout, "%s", "!!! Performed unknown optimization !!!");
      break;
    }
  if (self->value > 0 || self->position > -1)
    {
      fprintf (stdout, "%s", " (");
      bool printed = false;
      if (self->position > -1)
        {
          if (printed)
            fprintf (stdout, "%s", " - ");
          fprintf (stdout, "%s%d%s%d",
                   "Row: ", cell_to_row (self->position) + 1,
                   " - Column: ", cell_to_column (self->position) + 1);
          printed = true;
        }
      if (self->value > 0)
        {
          if (printed)
            fprintf (stdout, "%s", " - ");
          fprintf (stdout, "%s%d", "Value: ", self->value);
          printed = true;
        }
      fprintf (stdout, "%s", ")");
    }
}

/**
 * Given a vector of `log_item_t`s, determine how many
 * log items in the vector are of the specified type.
 */
int
get_log_count (const log_list_t *const restrict list, log_type_t type)
{
  unsigned int count = 0;
  for (unsigned int i = 0; i < list->size; i++)
    {
      if (list->at (list, i)->get_type (list->at (list, i)) == type)
        count++;
    }
  return count;
}

/**
 * Shuffle the values in an array of integers.
 */
void
shuffle_array (int *array, int size)
{
  for (int i = 0; i < size; i++)
    {
      int tail_size = size - i;
      int rand_tail_pos = rand () % tail_size + i;
      int temp = array[i];
      array[i] = array[rand_tail_pos];
      array[rand_tail_pos] = temp;
    }
}

symmetry_t
get_random_symmetry ()
{
  switch (rand () % 4)
    {
    case 0:
      return SYMMETRY_ROTATE90;
    case 1:
      return SYMMETRY_ROTATE180;
    case 2:
      return SYMMETRY_MIRROR;
    case 3:
      return SYMMETRY_FLIP;
    }
  return SYMMETRY_ROTATE90; // default
}

void
push (log_list_t *const restrict self, log_item_t *const restrict item)
{
  if (self->head == NULL)
    {
      self->head = (log_list_node_t *)malloc (sizeof (log_list_node_t));

      if (self->head == NULL)
        {
          fprintf (
              stderr, "%s\n",
              "Error: could not allocate memory for `log_list_node_t` object");
          exit (3);
        }

      self->head->item = item;
      self->head->next = NULL;
    }
  else
    {
      self->tail->next = (log_list_node_t *)malloc (sizeof (log_list_node_t));

      if (self->tail->next == NULL)
        {
          fprintf (stderr, "%s\n",
                   "Error: could not allocate memory for `log_list_t` object");
          exit (3);
        }

      self->tail->next->item = item;
      self->tail->next->next = NULL;
    }

  return;
}

log_item_t
pop (log_list_t *const restrict list)
{
  log_list_node_t *head = list->head;

  if (head == NULL)
    {
      fprintf (stderr, "%s\n", "Tried to pop empty list");
      exit (4);
    }

  log_item_t tmp = { 0 };
  if (head->next == NULL)
    {
      tmp = *(head->item);
      free (head);
      list->tail = NULL;
    }
  else
    {
      for (; head->next->next != NULL; head = head->next)
        ;
      tmp = *(head->next->item);
      free (head->next);
      list->tail = head;
    }
  return tmp;
}

log_item_t *
at (const log_list_t *const restrict list, size_t idx)
{
  if (idx > list->size)
    {
      fprintf (stderr, "%s\n", "idx out of bounds (list->at())");
      exit (5);
    }

  log_list_node_t *head = list->head;
  for (size_t i = 0; i < idx; i++, head = head->next)
    ;

  return head->item;
}

/**
 * Given the index of a cell ( 0-80 ) calculate
 * the column ( 0-8 ) in which that cell resides.
 */
static inline int
cell_to_column (int cell)
{
  return cell % ROW_COL_SEC_SIZE;
}

/**
 * Given the index of a cell ( 0-80 ) calculate
 * the row ( 0-8 ) in which it resides.
 */
static inline int
cell_to_row (int cell)
{
  return cell / ROW_COL_SEC_SIZE;
}

/**
 * Given the index of a cell ( 0-80 ) calculate
 * the section ( 0-8 ) in which it resides.
 */
static inline int
cell_to_section (int cell)
{
  return (cell / SEC_GROUP_SIZE * GRID_SIZE)
         + (cell_to_column (cell) / GRID_SIZE);
}

/**
 * Given the index of a cell ( 0-80 ) calculate
 * the cell ( 0-80 ) that is the upper left start
 * cell of that section.
 */
static inline int
cell_to_section_start_cell (int cell)
{
  return (cell / SEC_GROUP_SIZE * SEC_GROUP_SIZE)
         + (cell_to_column (cell) / GRID_SIZE * GRID_SIZE);
}

/**
 * Given a row ( 0-8) calculate the first cell (0-80 )
 * of that row.
 */
static inline int
row_to_first_cell (int row)
{
  return ROW_COL_SEC_SIZE * row;
}

/**
 * Given a column ( 0-8) calculate the first cell (0-80 )
 * of that column.
 */
static inline int
column_to_first_cell (int column)
{
  return column;
}

/**
 * Given a section ( 0-8) calculate the first cell (0-80 )
 * of that section.
 */
static inline int
section_to_first_cell (int section)
{
  return (section % GRID_SIZE * GRID_SIZE)
         + (section / GRID_SIZE * SEC_GROUP_SIZE);
}

/**
 * Given a value for a cell ( 0-8) and a cell (0-80 )
 * calculate the offset into the possibility array ( 0-728 ).
 */
static inline int
get_possibility_index (int value_index, int cell)
{
  return value_index + (ROW_COL_SEC_SIZE * cell);
}

/**
 * Given a row ( 0-8) and a column (0-8 ) calculate the
 * cell ( 0-80 ).
 */
static inline int
row_column_to_cell (int row, int column)
{
  return (row * ROW_COL_SEC_SIZE) + column;
}

/**
 * Given a section ( 0-8) and an offset into that section (0-8 )
 * calculate the cell ( 0-80 )
 */
static inline int
section_to_cell (int section, int offset)
{
  return section_to_first_cell (section)
         + ((offset / GRID_SIZE) * ROW_COL_SEC_SIZE) + (offset % GRID_SIZE);
}
