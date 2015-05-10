int GAP_PENALTY = 2;
int MATCH_SCORE = 1;
int MISSMATCH_SCORE = -1;

char arrows[255][255];

int run_smith_waterman = 0;

void print_matrix(int c_size, int r_size, int matrix[255][255], char *secuence1, char *secuence2);
int needleman_wunch_gap_penalty(int value, int penalty);
void init_standard_needleman_wunsch(int c_size, int r_size, int matrix[255][255]);
void print_simple_matrix (int c_size, int r_size, int matrix[255][255]);

int max(int a, int b) {
  int max;
  max = a > b ? a : b;
  return max;
}

int max_zero(int a, int b) {
  int max;
  max = a > b ? a : b;
	if (max < 0)
		max = 0;
  return max;
}