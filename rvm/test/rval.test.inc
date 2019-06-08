RTEST( "rval / NIL / is falsy" ) {
    rval nil = rnil();
    ASSERT( !rval_truthy( &nil ) );
} RTEST_END;

// subtype ops