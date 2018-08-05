# Chunk Search

Two utility classes for searching a single or more patterns in a sequence of data that are split accross several chunks. This can be useful e.g. when you need to search for pattern inside a large files and do not want/cannot read entire file into memory but have to read it partially.

Search methods accept pair of begin/end iterators for sequence where pattern(s) have to be searched for. Methods return a pair consisting of match length and sequence iterator to found pattern end position. If no match has been found, match length returned is 0.
