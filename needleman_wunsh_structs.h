struct Position {
  int row;
  int column;
};

struct CellAroundValues {
  int diagonal;
  int upper;
  int left;
};

struct MatchResults {
  int match;
  int upper_gap;
  int left_gap;
  int gap;
};
