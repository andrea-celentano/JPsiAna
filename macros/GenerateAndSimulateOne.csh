#!/bin/tcsh -f

#$1 is the "x" incrementing number (also the seed)
#$2 is the number of events

set DATADIR=$JPSIDATA
#set DATADIR=$ETAPIWORKDIR_FARM/data/signal_original
set RUNDIR=$JPSIANA_ROOT/run
set EXE1=$JPSIANA_ROOT/JPsiExe/generatePS
set EXE2=$JPSIANA_ROOT/JPsiExe/generatePhysics
set EXE3=$JPSIANA_ROOT/MonteCarloExe/doMonteCarlo

set DATACONFIG=$RUNDIR/MC.cfg
set MCCONFIG=conf5.dat

#set OUTFILE=$DATADIR/PseudoData_$1.root
set GENFILE=$DATADIR/gen_$1.root
set ACCFILE=$DATADIR/acc_$1.root

cd $RUNDIR

echo "Doing Phase Space"
set PSFILE=$DATADIR/PS_$1.root
$EXE1 -N $2 -s $1 -o $PSFILE
echo "Done Phase Space"

echo "Do Physics"
$EXE2 -c $DATACONFIG -i $PSFILE -o $GENFILE -s $1
echo "Done Physics"

echo "Removing PhaseSpace File: $PSFILE"
rm $PSFILE
echo "Done"

echo "Do MC"
$EXE3 $GENFILE $ACCFILE $MCCONFIG
echo "DONE"
