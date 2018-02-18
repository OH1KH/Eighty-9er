
//-------------------------------------------------------
void dump_state() {
  //this is a fake for clients like wsjt-x and fldigi who wants to see what the rig is capable of
 
strcpy(TXbuf,"\
0\n\
201\n\
1\n\
3500000.000000 3700000.000000 0x8006f -1 -1 0x4000000 0x3\n\
0 0 0 0 0 0 0\n\
3500000.000000 3700000.000000 0x8006f -1 -1 0x4000000 0x3\n\
0 0 0 0 0 0 0\n\
0x1ff 1\n\
0x1ff 0\n\
0 0\n\
0x1e 2200\n\
0x2 500\n\
0x1 8000\n");

writeCli();

strcpy(TXbuf,"\
0x1 2200\n\
0 0\n\
9000\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0xffffffffffffffff\n\
0xffffffffffffffff\n\
0xfffffffff7ffffff\n\
0xffffffff83ffffff\n\
0xffffffffffffffff\n\
0xffffffffffffffbf\n");

writeCli();
}

//-------------------------------------------------------
   // See dump_state in rigctl_parse.c for what this means.
//            out << "0\n"; // protocol version
//            out << "2" << "\n"; //RIG_MODEL_NETRIGCTL
//            out << "1" << "\n"; //RIG_ITU_REGION1
//            RX: start, end, modes,low_power,High_power, vfo,ant
//            out << "150000.000000 30000000.000000  0x900af -1 -1 0x10000003 0x3\n"; //("%"FREQFMT" %"FREQFMT" 0x%x %d %d 0x%x 0x%x\n",start,end,modes,low_power,high_power,vfo,ant)
//            out << "0 0 0 0 0 0 0\n";
//            TX: start, end, modes,low_power,High_power, vfo,ant
//            out << "150000.000000 30000000.000000  0x900af -1 -1 0x10000003 0x3\n"; //TX
//            out << "0 0 0 0 0 0 0\n";
//            Tuning steps: modes,steps
//            out << "0 0\n";
//            Filters: modes,width
//            out << "0 0\n";
//            Channel list zero ended
//            out << "0\n"; max rit
//            out << "0\n"; max xit
//            out << "0\n"; max if shift
//            out << "0\n"; announces
//            out << "\n";  preamp
//            out << "\n";  attenuator
//            out << "0x0\n"; has get func
//            out << "0x0\n"; has set func
//            out << "0x0\n"; has get level
//            out << "0x0\n"; has set level
//            out << "0x0\n"; has get parm
//            out << "0\n";   has set parm
//            output = true;
//       }
/*
 *  For rigctld internal use 
declare_proto_rig(dump_state)
{
    int i;
    struct rig_state *rs = &rig->state;

    /*
     * - Protocol version
     *
#define RIGCTLD_PROT_VER 0
    fprintf(fout, "%d\n", RIGCTLD_PROT_VER);
    fprintf(fout, "%d\n", rig->caps->rig_model);
    fprintf(fout, "%d\n", rs->itu_region);

    for (i = 0; i < FRQRANGESIZ && !RIG_IS_FRNG_END(rs->rx_range_list[i]); i++)
    {
        fprintf(fout,
                "%"FREQFMT" %"FREQFMT" 0x%x %d %d 0x%x 0x%x\n",
                rs->rx_range_list[i].start,
                rs->rx_range_list[i].end,
                rs->rx_range_list[i].modes,
                rs->rx_range_list[i].low_power,
                rs->rx_range_list[i].high_power,
                rs->rx_range_list[i].vfo,
                rs->rx_range_list[i].ant);
    }

    fprintf(fout, "0 0 0 0 0 0 0\n");

    for (i = 0; i < FRQRANGESIZ && !RIG_IS_FRNG_END(rs->tx_range_list[i]); i++)
    {
        fprintf(fout,
                "%"FREQFMT" %"FREQFMT" 0x%x %d %d 0x%x 0x%x\n",
                rs->tx_range_list[i].start,
                rs->tx_range_list[i].end,
                rs->tx_range_list[i].modes,
                rs->tx_range_list[i].low_power,
                rs->tx_range_list[i].high_power,
                rs->tx_range_list[i].vfo,
                rs->tx_range_list[i].ant);
    }

    fprintf(fout, "0 0 0 0 0 0 0\n");

    for (i = 0; i < TSLSTSIZ && !RIG_IS_TS_END(rs->tuning_steps[i]); i++)
    {
        fprintf(fout,
                "0x%x %ld\n",
                rs->tuning_steps[i].modes,
                rs->tuning_steps[i].ts);
    }

    fprintf(fout, "0 0\n");

    for (i = 0; i < FLTLSTSIZ && !RIG_IS_FLT_END(rs->filters[i]); i++)
    {
        fprintf(fout,
                "0x%x %ld\n",
                rs->filters[i].modes,
                rs->filters[i].width);
    }

    fprintf(fout, "0 0\n");

#if 0
    chan_t chan_list[CHANLSTSIZ]; /*!< Channel list, zero ended *
#endif

    fprintf(fout, "%ld\n", rs->max_rit);
    fprintf(fout, "%ld\n", rs->max_xit);
    fprintf(fout, "%ld\n", rs->max_ifshift);
    fprintf(fout, "%d\n", rs->announces);

    for (i = 0; i < MAXDBLSTSIZ && rs->preamp[i]; i++)
    {
        fprintf(fout, "%d ", rs->preamp[i]);
    }

    fprintf(fout, "\n");

    for (i = 0; i < MAXDBLSTSIZ && rs->attenuator[i]; i++)
    {
        fprintf(fout, "%d ", rs->attenuator[i]);
    }

    fprintf(fout, "\n");

    fprintf(fout, "0x%lx\n", rs->has_get_func);
    fprintf(fout, "0x%lx\n", rs->has_set_func);
    fprintf(fout, "0x%lx\n", rs->has_get_level);
    fprintf(fout, "0x%lx\n", rs->has_set_level);
    fprintf(fout, "0x%lx\n", rs->has_get_parm);
    fprintf(fout, "0x%lx\n", rs->has_set_parm);

#if 0
    gran_t level_gran[RIG_SETTING_MAX];   /*!< level granularity *
    gran_t parm_gran[RIG_SETTING_MAX];  /*!< parm granularity *
#endif

    return RIG_OK;
}


/* '3' *
declare_proto_rig(dump_conf)
{
    dumpconf(rig, fout);

    return RIG_OK;
}


 */
