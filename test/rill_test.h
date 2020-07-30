typedef struct rts rts;

rts * rts_create ();
int rts_begin_test ( rts * ts, const char * name );
int rts_assert ( rts * ts, int cond, const char * txt );
void rts_report_test ( rts * ts );
void rts_end_test ( rts * ts );
void rts_report_all ( rts * ts );
int rts_successful ( rts * ts );
