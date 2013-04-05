#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char** argv) {

  if(argc!=3) {
    //usage() ;
    exit(1);
  }

  int fd = open(argv[2],O_WRONLY | O_CREAT, 0666);
  
  char* s = "#include <cairo/cairo.h>\n#include <cairo/cairo-pdf.h>\n\nint main (void){\n\tcairo_surface_t * surface;\n\tcairo_t * cr;\n\tcairo_surface_t * pdf_surface = cairo_pdf_surface_create(" ;
  write(fd,s,strlen(s)*sizeof(char));

  

  close(fd);

  return 0 ;

}

  
