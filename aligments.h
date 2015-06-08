#include "alignment_support.h"
#include "needleman_wunsh_structs.h"

int GAP_PENALTY = 2;
int MATCH_SCORE = 1;
int MISSMATCH_SCORE = -1;

char arrows[255][255];

int run_smith_waterman = 0;



void init_arrow_matrix() {
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < 255; j++) {
      arrows[i][j] = 0x00;
    }
  }
}

int gap_penalty(int value, int penalty) {
  return (value - penalty);
}

int process_match(char column_char_value, char row_char_value, int evaluation_value) {
  int match_value;
  match_value = (column_char_value == row_char_value) ? MATCH_SCORE : MISSMATCH_SCORE;
  return evaluation_value + match_value;
}

void cell_match_results(char column_secuence_char, char row_secuence_char, struct CellAroundValues values, struct MatchResults *results) {
  int upper_gap, left_gap;
  results->match = process_match(column_secuence_char, row_secuence_char, values.diagonal);
  upper_gap = gap_penalty(values.upper, GAP_PENALTY);
  left_gap = gap_penalty(values.left, GAP_PENALTY);
  results->upper_gap = upper_gap;
  results->left_gap = left_gap;
  results->gap = max(upper_gap, left_gap);
}

void init_standard_needleman_wunsch(int c_size, int r_size, int matrix[255][255]) {
  int i, j;
  for(i = 1; i < r_size; i++) {
    matrix[i][0] = gap_penalty(matrix[i - 1][0], GAP_PENALTY);
    arrows[i][0] = 0x01;
  }

  for(j = 1; j < c_size; j++) {
    matrix[0][j] = gap_penalty(matrix[0][j - 1], GAP_PENALTY);
    arrows[0][j] = 0x04;
  }
}

void set_direction(struct Position pos, struct MatchResults match_results) {
  char direction = 0x00;
  if (match_results.upper_gap > match_results.match) {
    if (match_results.upper_gap > match_results.left_gap)
      direction = 0x01;
    else if(match_results.upper_gap > match_results.left_gap)
      direction = 0x04;
    else
      direction = 0x05;
  }
  else if (match_results.upper_gap < match_results.match) {
    if (match_results.upper_gap > match_results.left_gap)
      direction = 0x02;
    else if(match_results.upper_gap < match_results.left_gap)
      direction = 0x04;
    else
      direction = 0x06;
  }
  else {
    if (match_results.upper_gap < match_results.left_gap)
     direction = 0x04;
    else
     direction = 0x07;
  }

  arrows[pos.row][pos.column] = direction;
}

int process_NW_cell_value(struct Position pos, char column_secuence_char, char row_secuence_char, struct CellAroundValues values) {
  struct MatchResults match_results;
  cell_match_results(column_secuence_char, row_secuence_char, values, &match_results);
  set_direction(pos, match_results);
  return max(match_results.match, match_results.gap);
}

void process_needleman_wunsch(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  int i, j;

  for(i = 1; i < r_size; i++) {
    for(j = 1; j < c_size; j++) {
      struct Position cell_position;
      struct CellAroundValues cell_values;
      cell_position.row = i;
      cell_position.column = j;
      cell_values.upper = values[i - 1][j];
      cell_values.diagonal = values[i- 1][j -1];
      cell_values.left = values[i][j - 1];
      values[i][j] = process_NW_cell_value(cell_position, secuence1[j - 1], secuence2[i - 1], cell_values);
    }
  }
}

int *needleman_wunsch(int values[255][255], char *secuence1, char *secuence2) {
  int c_size, r_size;
  c_size = (int) strlen(secuence1) + 1;
  r_size = ((int) strlen(secuence2)) + 1;
  init_matrix(c_size, r_size, values);
  init_standard_needleman_wunsch(c_size, r_size, values);
  process_needleman_wunsch(c_size, r_size, values, secuence1, secuence2);
}

int process_SW_cell_value(struct Position pos, char column_secuence_char, char row_secuence_char, struct CellAroundValues values) {
  struct MatchResults match_results;
  cell_match_results(column_secuence_char, row_secuence_char, values, &match_results);
  return max_zero(match_results.match, match_results.gap);
}

void process_smith_waterman(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  int i, j;

  for(i = 1; i < r_size; i++) {
    for(j = 1; j < c_size; j++) {
      struct Position cell_position;
      struct CellAroundValues cell_values;
      cell_position.row = i;
      cell_position.column = j;
      cell_values.upper = values[i - 1][j];
      cell_values.diagonal = values[i- 1][j -1];
      cell_values.left = values[i][j - 1];
      values[i][j] = process_SW_cell_value(cell_position, secuence1[j - 1], secuence2[i - 1], cell_values);
    }
  }
}

int *smith_waterman(int values[255][255], char *secuence1, char *secuence2) {
  int c_size, r_size;
  c_size = (int) strlen(secuence1) + 1;
  r_size = ((int) strlen(secuence2)) + 1;
  init_matrix(c_size, r_size, values);
  process_smith_waterman(c_size, r_size, values, secuence1, secuence2);
}