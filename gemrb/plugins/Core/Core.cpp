/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/Core.cpp,v 1.5 2003/12/09 23:09:07 avenger_teambg Exp $
 *
 */

// Core.cpp : Defines the entry point for the DLL application.
//

#ifndef WIN32
#include <ctype.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#else
#include <windows.h>
#include <sys\stat.h>

BOOL WINAPI DllEntryPoint( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	return true;
}
#endif

#include "../../includes/globals.h"

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif

#ifdef WIN32

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

//// Globally used functions
GEM_EXPORT bool dir_exists(const char *path)
{
        struct stat buf;

        buf.st_mode=0;
        stat(path, &buf);
        return S_ISDIR(buf.st_mode);
}

//// Compatibility functions
#ifdef WIN32

#else
char * FindInDir(char * Dir, char * Filename)
{
        char * fn = NULL;
        DIR * dir = opendir(Dir);
        if(dir == NULL)
                return NULL;
        struct dirent * de = readdir(dir);
        if(de == NULL)
                return NULL;
        do {
                if(strcasecmp(de->d_name, Filename ) == 0) {
                        fn = (char*)malloc(strlen(de->d_name)+1);
                        strcpy(fn, de->d_name);
                        break;
                }
        } while((de = readdir(dir)) != NULL);
        closedir(dir);  //No other files in the directory, close it
        return fn;
}

char *strupr(char *string)
{
        char *s;
        if(string)
        {
                for(s = string; *s; ++s)
                        *s = toupper(*s);
        }
        return string;
}

char *strlwr(char *string)
{
        char *s;
        if(string)
        {
                for(s = string; *s; ++s)
                        *s = tolower(*s);
        }
        return string;
}

void ResolveFilePath(char *FilePath)
{
        char TempFilePath[_MAX_PATH];
        char TempFileName[_MAX_PATH];
        int j, pos;

        TempFilePath[0]=FilePath[0];
        for(pos=1;FilePath[pos] && FilePath[pos]!='/';pos++)
                TempFilePath[pos]=FilePath[pos];
        TempFilePath[pos]=0;
        while(FilePath[pos]=='/') {
                pos++;
                for(j=0;FilePath[pos+j] && FilePath[pos+j]!='/';j++) {
                        TempFileName[j]=FilePath[pos+j];
                }
                TempFileName[j]=0;
                pos+=j;
                char *NewName = FindInDir(TempFilePath, TempFileName);
                if(NewName) {
                        strcat(TempFilePath, SPathDelimiter);
                        strcat(TempFilePath, NewName);
                        free(NewName);
                }
                else {
			if(j)
	                        return;
			else {
				strcat(TempFilePath, SPathDelimiter);
			}	
		}
        }
        //should work (same size)
	printf("Old filepath: %s\n",FilePath);
        strcpy(FilePath,TempFilePath);
	printf("New filepath: %s\n",FilePath);
}

#endif


