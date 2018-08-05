# chunk_search
Search performed sequentially on chunks of data.

Two utility classes that enable to search for a single or more patterns in sequence of data that are split accross several chunks. This can be useful e.g. when you need to search for pattern inside large files and do not want/cannot read entire file into memory but have to read it by chunks.

Search methods accept pair of begin/end iterators for sequence where pattern(s) have to be searched for. They return a pair consisting of match length and sequence iterator to found pattern end position. If no match has been found, match length returned is 0.
