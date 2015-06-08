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

void init_matrix(int c_size, int r_size, int matrix[255][255]) {
  int i, j;

  matrix[0][0] = 0;
  for (i = 1; i < r_size; i++) {
    for (j = 1; j < c_size; j++) {
      if (i != 0 && j != 0) {
        matrix[i][j] = 0;
      }
    }
  }
}

char *int_to_string(int value) {
  static char str[5];
  sprintf(str, "%d", value);
  return str;
}