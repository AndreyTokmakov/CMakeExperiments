

=============================================================================================================================================================
                    Filesystem commands |          https://cmake.org/cmake/help/latest/command/file.html        
=============================================================================================================================================================

• Reading

     file(READ <filename> <out-var> [...])
     file(STRINGS <filename> <out-var> [...])
     file(<HASH> <filename> <out-var>)
     file(TIMESTAMP <filename> <out-var> [...])

• Writing

     file({WRITE | APPEND} <filename> <content>...)
     file({TOUCH | TOUCH_NOCREATE} <file>...)
     file(GENERATE OUTPUT <output-file> [...])
     file(CONFIGURE OUTPUT <output-file> CONTENT <content> [...])

• Filesystem

     file({GLOB | GLOB_RECURSE} <out-var> [...] <globbing-expr>...)
     file(MAKE_DIRECTORY <directories>...)
     file({REMOVE | REMOVE_RECURSE } <files>...)
     file(RENAME <oldname> <newname> [...])
     file(COPY_FILE <oldname> <newname> [...])
     file({COPY | INSTALL} <file>... DESTINATION <dir> [...])
     file(SIZE <filename> <out-var>)
     file(READ_SYMLINK <linkname> <out-var>)
     file(CREATE_LINK <original> <linkname> [...])
     file(CHMOD <files>... <directories>... PERMISSIONS <permissions>... [...])
     file(CHMOD_RECURSE <files>... <directories>... PERMISSIONS <permissions>... [...])     