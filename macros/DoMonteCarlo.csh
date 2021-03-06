#!/bin/tcsh -f





#set FNAME=$JPSIDATA/gen_*.root
set MONTECARLOEXE=$JPSIANA_ROOT/MonteCarloExe/doMonteCarlo

set RUNDIR=$JPSIANA_ROOT/run
set CFILE=conf5.dat

set QUEUE=long
cd $JPSIDATA
rm *MC.out.log
rm *MC.err.log
set N = `ls -l gen_*.root | egrep -c '^-'`
cd $RUNDIR

echo "There are $N files"
set NN = $N
@ NN = $N - 1

echo $NN
foreach x (`seq 0 1 $NN`)
    set INFILE=$JPSIDATA/gen_$x.root
    set OUTFILE=$JPSIDATA/acc_$x.root
    rm -f $OUTFILE
    echo "Processing $INFILE -> Output will be $OUTFILE"
    bsub -q $QUEUE -P sl5_64 -o $JPSIDATA/$x.MC.out.log -e $JPSIDATA/$x.MC.err.log -R "rusage[mem=3000,swp=3500]" $MONTECARLOEXE $INFILE $OUTFILE $CFILE
end

