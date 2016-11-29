#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);
  transform = make_scale(1,2,3);
  printf("Scale\n");
  print_matrix(transform);
  add_edge(edges,1,2,3,2,3,4);
  printf("Original Edge\n");
  print_matrix(edges);
  matrix_mult(transform,edges);
  printf("Edge after Scale\n");
  print_matrix(edges);
  transform = make_translate(2,3,4);
  matrix_mult(transform,edges);
  printf("Translate MatrixZ\n");
  print_matrix(transform);
  printf("Edge after Translate\n");
  print_matrix(edges);
  printf("Rotating matrixZ\n");
  transform = make_rotZ(30);
  print_matrix(transform);
  printf("Edge after rotZ\n");
  matrix_mult(transform,edges);
  print_matrix(edges);
  printf("Rotating matrixY\n");
  transform = make_rotY(30);
  print_matrix(transform);
  printf("Edge after rotY\n");
  matrix_mult(transform,edges);
  print_matrix(edges);
  printf("Rotating matrixX\n");
  transform = make_rotX(30);
  print_matrix(transform);
  printf("Edge after rotX\n");
  matrix_mult(transform,edges);
  print_matrix(edges);
  parse_file( "script_c", transform, edges, s );

  free_matrix( transform );
  free_matrix( edges );
}  
