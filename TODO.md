(*) - Important

CMake:
	1. Exclude Debug configuration while building SDL. Current fix: Disabled build of a shared SDL library.
	2. Cut out MinSizeRel, RelWithDebInfo?
	3. Separate debug and release libs.
	4. Add filters for game src.
	5. Use modules from corresponding library directories.
	6. Compiler flags.
	7. Add license.
	8. Print version info for each library.
	*9. Set build directory (debug, release).
	10. Fix CMP0054 messages.
	11. Cut out tests from libraries. Or separate them to another project?

Code convention:
	1. Set up checker tool.

Libraries:
	1. Add FreeImage or similar.
	2. Add FreeType or similar.
	3. Add recastnavigation.