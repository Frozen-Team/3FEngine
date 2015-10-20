function(ADD_FILTERS SOURCES RELATIVE_DIR)
	foreach(f ${SOURCES})
	    # Get the path of the file relative to ${DIRECTORY},
	    # then alter it (not compulsory)
	    file(RELATIVE_PATH SRCGR ${RELATIVE_DIR} ${f})
	    set(SRCGR "src/${SRCGR}")
	    # Extract the folder, ie remove the filename part
	    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
	    # Source_group expects \\ (double antislash), not / (slash)
	    string(REPLACE / \\ SRCGR ${SRCGR})
	    source_group("${SRCGR}" FILES ${f})
	endforeach()
endfunction(ADD_FILTERS)