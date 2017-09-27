
top_makefile=$(base_dir)/Makefile

#######################################
#######  DIRECTORY DECLARATIONS ########
#######################################

base_dir=$(shell pwd)
inc_dir=$(base_dir)/inc
output_dir=$(base_dir)/output
output_objdir=$(output_dir)/obj
output_libdir=$(output_dir)/lib
output_static_libdir=$(output_libdir)/static
output_shared_libdir=$(output_libdir)/shared
output_appdir=$(output_dir)/app

SUBDIRS=src

#######################################
#######  FLAGS DECLARATIONS ########
#######################################

CC=gcc
CFLAGS= -O2 -Wall
CFLAGS_DEBUG= -g
CFLAGS_SHARED_LIB= -fpic -c
INC=-I$(inc_dir)
AR=ar

#######################################
#########  EXPORT VARIABLES ###########
#######################################
export base_dir
export inc_dir
export output_dir
export output_objdir 
export output_static_libdir 
export output_shared_libdir 
export output_appdir 
export top_makefile
export CFLAGS
export CFLAGS_DEBUG
export CFLAGS_SHARED_LIB
export INC

#.PHONY:	all debug clean cleanAll
.PHONY:	all clean cleanAll


#######################################
###########  TARGET RULES #############
#######################################

all:
	@for d in $(SUBDIRS) ; do	\
		make -C $$d all; \
	done

debug:
	@for d in $(SUBDIRS) ; do	\
		make -C $$d debug; \
	done


clean:
	@for d in $(SUBDIRS) ; do	\
		#echo "DIR: $$d DIR"; \
		make -C $$d clean; \
	done
	

cleanAll:	clean
	rm -rf $(output_dir)/obj/
	rm -rf $(output_dir)/lib/
	rm -rf $(output_dir)/app/
	
