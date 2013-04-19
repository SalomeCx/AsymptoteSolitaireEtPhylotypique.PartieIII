#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include "draw.tab.h"


void usage(char* cmd) {
	printf("Usage : %s fileSrc [fileDst] - optionnel\n", cmd ) ;
}

int main(int argc, char** argv) {

  if(argc!=3 && argc != 2) {
    usage(argv[0]) ;
    exit(1);
  }

  int fd_dst ;

  if(argc == 3) {
  	fd_dst = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0666);
  	dup2(fd_dst,1);
  }

  int fd_src = open(argv[1] , O_RDONLY ) ;
  dup2(fd_src,0);
  
  printf("#include <cairo/cairo.h>\n\
#include <cairo/cairo-pdf.h>\n\n\
int main (void){\n\
cairo_surface_t * surface;\n\
cairo_t * cr;\n\
cairo_surface_t * pdf_surface = cairo_pdf_surface_create(\"%s.pdf\",500,500);\n\
cr = cairo_create ( pdf_surface );\n" , argv[2] ) ;

  yyparse() ;

  printf("cairo_destroy ( cr );\ncairo_surface_destroy ( pdf_surface );\nreturn 0; \n}") ;

  close(fd_src);

  if( argc == 3)
  	close(fd_dst) ;

  return 0 ;

}

  
