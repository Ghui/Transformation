#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         l: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 i: set the transform matrix to the identity matrix - 
	 s: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 t: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 x: create an x-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 y: create an y-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 z: create an z-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 a: apply the current transformation matrix to the 
	    edge matrix
	 v: draw the lines of the edge matrix to the screen
	    display the screen
	 g: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 q: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)

jdyrlandweaver
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * pm,
                  screen s) {
  char temp;
  float a,b,c,d,e,f;
  int i,j;
  char * ImgName;
  FILE * file = fopen(filename, "r");
  while(fscanf(file,"%c", &temp) ==1){
    //add edge
    if(temp == 'l'){
      fscanf(file,"%c",&temp);
      if(fscanf(file,"%f %f %f %f %f %f",&a,&b,&c,&d,&e,&f) == 6)
	add_edge(pm,a,b,c,d,e,f);
      else
	printf("SomeThings wrong that need to be fix in l\n");
    }
    //ident transform
    else if(temp == 'i'){
      ident(transform);
    }
    //scaling
    else if(temp == 's'){
      fscanf(file,"%c",&temp);
      if(fscanf(file,"%f %f %f", &a,&b,&c) == 3){
	struct matrix * scalar = make_scale(a,b,c);
	matrix_mult(scalar,transform);
      }
      else
	printf("Somethings wrong that need to be fix in s\n");
    }
    //Translating
    else if (temp == 't'){
      fscanf(file,"%c",&temp);
      if(fscanf(file,"%f %f %f", &d,&e,&f) == 3){
	struct matrix * tranlator = make_translate(d,e,f);
	matrix_mult(tranlator, transform);
      }
      else
	printf("somethings wrong that need to be fix in t\n");
    }
    //Rotating with x
    else if(temp == 'x'){
      fscanf(file,"%c",&temp);
      if(fscanf(file,"%f",&a) ==1){
	struct matrix * rotX = make_rotX(a);
	matrix_mult(rotX,transform);
      }
      else{
	printf("something wrong that need to be fix in x\n");
      }
    }
    //Rotating with Y
    else if(temp == 'y'){
      fscanf(file,"%c",&temp);
      if(fscanf(file,"%f",&b) ==1){
	struct matrix * rotY = make_rotY(b);
	matrix_mult(rotY,transform);
      }
      else{
	printf("something wrong that need to be fix in y\n");
      }
    }
    //Rotating with Z
    else if(temp == 'z'){
      fscanf(file,"%c",&temp);
      if(fscanf(file,"%f",&c) ==1){
	struct matrix * rotZ = make_rotZ(a);
	matrix_mult(rotZ,transform);
      }
      else{
	printf("something wrong that need to be fix in z\n");
      }
    }
    //Applying Transformation
    else if(temp == 'a'){
      matrix_mult(transform,pm);
    }
    else if(temp == 'v'){
      color c;
      c.red = 122;
      c.green = 218;
      c.blue = 225;
      
      clear_screen(s);
      for( i=0; i<XRES; i++){
	for ( j=0; j<YRES; j++){

	  //c.red = random() % (MAX_COLOR + 1);
	  //c.green = random() % (MAX_COLOR + 1);
	  //c.blue = random() % (MAX_COLOR + 1);
	  plot( s, c, i, j);
	}
      }
      c.green = 40;
      draw_lines(pm,s,c);
      display(s);
    }
    else if(temp == 'g'){
      color c;
      c.red = 122;
      c.green = 218;
      c.blue = 225;
      
      clear_screen(s);
      for( i=0; i<XRES; i++){
	for ( j=0; j<YRES; j++){

	  //c.red = random() % (MAX_COLOR + 1);
	  //c.green = random() % (MAX_COLOR + 1);
	  //c.blue = random() % (MAX_COLOR + 1);
	  plot( s, c, i, j);
	}
      }
      c.green = 40;
      draw_lines(pm,s,c);
      ImgName = (char *)malloc(256);

      fscanf(file,"%c",&temp);
      if(fscanf(file,"%s",ImgName) ==1){
	  ImgName = strsep(&ImgName, ".");
	  save_ppm(s,ImgName);
	  ImgName = strncat(ImgName,".png",4);
	  save_extension(s,ImgName);
	  free(ImgName);
	}
      else
	printf("Something wrong that need to be fix in g\n");
    }
    else if (temp == 'q'){
      return;
    }
  }
}

  
