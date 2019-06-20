RTEST( "rval / NIL / is falsy" ) {
    rval nil = rnil();
    ASSERT( !rval_truthy( &nil ) );
} RTEST_END;
/*
    subtype
    subtype is carried between clone()s and copies()
    deepclone
*/
