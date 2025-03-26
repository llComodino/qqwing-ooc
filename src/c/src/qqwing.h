#pragma once

#include <stddef.h>

#define VERSION "1.3.4"
#define PACKAGE_STRING "qqwing 1.3.4"

#define GRID_SIZE         (3)
#define ROW_COL_SEC_SIZE  (GRID_SIZE * GRID_SIZE)
#define SEC_GROUP_SIZE    (ROW_COL_SEC_SIZE * GRID_SIZE)
#define BOARD_SIZE        (ROW_COL_SEC_SIZE * ROW_COL_SEC_SIZE)
#define POSSIBILITY_SIZE  (BOARD_SIZE * ROW_COL_SEC_SIZE)

char* get_version();

typedef enum {
  ONE_LINE,
  COMPACT,
  READABLE,
  CSV
} print_style_t;

typedef enum {
  UNKNOWN,
  SIMPLE,
  EASY,
  INTERMEDIATE,
  EXPERT
} difficulty_t;

typedef enum {
  SYMMETRY_NONE,
  SYMMETRY_ROTATE90,
  SYMMETRY_ROTATE180,
  SYMMETRY_MIRROR,
  SYMMETRY_FLIP,
  SYMMETRY_RANDOM
} symmetry_t;

typedef struct sudoku_board_t sudoku_board_t;
typedef sudoku_board_t * self_t;

struct sudoku_board_t* new_sudoku_board(void);
bool set_puzzle(self_t self, int* init_puzzle);
const int* get_puzzle(self_t self);
const int* get_solution(self_t self);
void print_puzzle(self_t self);
void print_solution(self_t self);
bool solve(self_t self);
int count_solutions(self_t self, bool limited);
bool has_unique_solution(self_t self);
bool is_solved(self_t self);
void print_solve_history(self_t self);
void set_record_history(self_t self, bool rec_history);
void set_log_history(self_t self, bool log_hist);
void set_print_style(self_t self, print_style_t ps);
bool generate_puzzle_symmetry(self_t self, symmetry_t symmetry);
int get_given_count(self_t self);
int get_single_count(self_t self);
int get_hidden_single_count(self_t self);
int get_naked_pair_count(self_t self);
int get_hidden_pair_count(self_t self);
int get_box_line_reduction_count(self_t self);
int get_pointing_pair_triple_count(self_t self);
int get_guess_count(self_t self);
int get_backtrack_count(self_t self);
void print_solve_instructions(self_t self);
difficulty_t get_difficulty(self_t self);
char* get_difficulty_as_string(self_t self);

typedef enum {
  GIVEN,
  SINGLE,
  HIDDEN_SINGLE_ROW,
  HIDDEN_SINGLE_COLUMN,
  HIDDEN_SINGLE_SECTION,
  GUESS,
  ROLLBACK,
  NAKED_PAIR_ROW,
  NAKED_PAIR_COLUMN,
  NAKED_PAIR_SECTION,
  POINTING_PAIR_TRIPLE_ROW,
  POINTING_PAIR_TRIPLE_COLUMN,
  ROW_BOX,
  COLUMN_BOX,
  HIDDEN_PAIR_ROW,
  HIDDEN_PAIR_COLUMN,
  HIDDEN_PAIR_SECTION
} log_type_t;

typedef struct log_item_t log_item_t;

struct log_item_t* new_std_log(int round, log_type_t type);
struct log_item_t* new_val_pos_log(int round, log_type_t type, int value, int position);

typedef struct log_list_node_t {
  log_item_t *item;
  struct log_list_node_t *next;
  struct log_list_node_t *prev;
} log_list_node_t;

typedef struct log_list_t {
  log_list_node_t *head;
  log_list_node_t *tail;

  size_t size;

  void (*push)(struct log_list_t *const, log_item_t *const);
  log_item_t (*pop)(struct log_list_t *const);
  log_item_t* (*at)(const struct log_list_t *const , size_t);
} log_list_t;
