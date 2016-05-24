#FiveCpp Borland make

BCDIR=c:\bcc582

.path.obj = .\obj
.path.h   = .\include
.path.cpp = .\source\classes
.path.lib = .\lib

FILES = \
.\source\classes\array.cpp \
.\source\classes\codeblk.cpp \
.\source\classes\menu.cpp \
.\source\classes\msgbar.cpp \
.\source\classes\string.cpp \
.\source\classes\window.cpp \
.\source\classes\msgs.cpp   

OBJ = $(FILES:.cpp=.obj)
OBJS = $(OBJ:.\source\classes\=.\obj\) 

PROJECT : fivecpp.lib

fivecpp.lib : $(OBJS)

$(OBJS) : fivecpp.h

.cpp.obj: 
   $(BCDIR)\bin\bcc32 -c -I.\include -o.\obj\$& $< 
   $(BCDIR)\bin\tlib .\lib\fivecpp.lib -+ .\obj\$&

clean:
   @del obj\* /Q
   @del lib\* /Q
   @del samples\*.exe /Q
   @del samples\*.obj /Q
   @del samples\*.tds /Q