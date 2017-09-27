#base_dir=/home/shrini/shrinivas/Dev/my_progs/baseLibs

#top_makefile=$(base_dir)/Makefile

#######################################
#######  DIRECTORY DECLARATIONS ########
#######################################

#base_dir=$(shell pwd)
#inc_dir=$(base_dir)/inc
#output_dir=$(base_dir)/output
#output_objdir=$(output_dir)/obj
#output_libdir=$(output_dir)/lib
#output_appdir=$(output_dir)/app

SUBDIRS=ds

#######################################
#######  FLAGS DECLARATIONS ########
#######################################

CC=gcc
CFLAGS= -O2
CFLAGS_DEBUG= -g
INC=-I$(inc_dir)
AR=ar

#######################################
#########  EXPORT VARIABLES ###########
#######################################
export base_dir
export inc_dir
export output_dir
export output_objdir 
export output_libdir 
export output_appdir 
export top_makefile
export CFLAGS
export INC
export CFLAGS_DEBUG

.PHONY:	all debug clean


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
	

#cleanAll:	clean
#	rm -f $(output_objdir)/*
#	rm -f $(output_libdir)/*
#	rm -f $(output_appdir)/*
	
