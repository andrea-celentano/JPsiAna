/*
This amplitude is for the eta-pi photoproduction, in the case of a double-regge exchange 
The formula is given in the document V. Mathieud gave me.

It is NOT in covariant form: 4-vectors have to be reported in the GJ frame of eta - pi. But this is handled in CLAS12PhotonsDataReader automatically!

 */

#include <cassert>
#include <iostream>
#include <string>
#include <complex>
#include <cstdlib>
#include <cmath>
#include "IUAmpTools/Kinematics.h"
#include "JPsiAmp/Resonance.h"


/*parameters are: 
0  helicity_electron_beam    -> not used here, but in parent class
1  helicity_electron_recoil  -> not used here, but in parent class
2  helicity_target
3  helicity_recoil_proton
4  ID of the electron counting from 0 -> not used here, but in parent class 
 */
Resonance::Resonance(const vector<string> &args) ://beam electron target recoil
Clas12PhotonsAmplitude(args),
m_params(args)
{
	m_helicity_target=atoi(args[2].c_str());
	m_helicity_recoil=atoi(args[3].c_str());

	m_deltaHelicity_leptons=atoi(args[5].c_str());
	m_couplingIp=AmpParameter(args[6].c_str()); //initial coupling, positive helicity for the photon
	m_couplingIm=AmpParameter(args[7].c_str()); //initial coupling, negative helicity for the photon
	m_couplingFp=AmpParameter(args[8].c_str());  //final  coupling, positive helicity for the J
	m_couplingFm=AmpParameter(args[9].c_str());  //final  coupling, negative helicity for the J

	registerParameter(m_couplingIp);
	registerParameter(m_couplingIm);
	registerParameter(m_couplingFp);
	registerParameter(m_couplingFm);
}

/*Order of the particles in pKin:
0  beam (THE ELECTRON!)
1  target
2  eprime
3  proton
4  ePlus
5  eMinus
 */


complex< GDouble > Resonance::calcHelicityAmplitude(int helicity,GDouble** pKin ) const{


	if (helicity==0) return complex<GDouble> (0.,0.); //put this here because for a longitudinal quasi-real photon the amplitude is 0, don't go further!

	TLorentzVector Pbeam(pKin[0][1], pKin[0][2],
			pKin[0][3], pKin[0][0]);

	TLorentzVector Ptarget(pKin[1][1], pKin[1][2],
			pKin[1][3], pKin[1][0]);

	TLorentzVector Peprime(pKin[2][1], pKin[2][2],
			pKin[2][3], pKin[2][0]);

	TLorentzVector Pproton(pKin[3][1], pKin[3][2],
			pKin[3][3], pKin[3][0]);

	TLorentzVector PePlus(pKin[4][1], pKin[4][2],
			pKin[4][3], pKin[4][0]);

	TLorentzVector PeMinus(pKin[5][1], pKin[5][2],
			pKin[5][3], pKin[5][0]);



	TLorentzVector Pg,Ppsi;
	GDouble s,t;
	GDouble thetaDecay,phiDecay;
	GDouble thetaProd,phiProd;

	//The amplitude
	complex<double> amp(1.,0.);
	complex<double> ampP(1.,0.);
	complex<double> ampM(1.,0.);
	complex<double> ampDecayP(1.,0.);
	complex<double> ampDecayM(1.,0.);

	complex<double> i(0.,1.);
	complex<double> one(1.,0.);


	//1:define the photon beam and the JPsi
	Pg=Pbeam-Peprime;
	Ppsi=PePlus+PeMinus;



	//2: for the Psi decay, there is a term D*_(lambdaGamma,deltaLambdaLeptons) (phi2,theta2,0)
	//Where phi2 and theta2 are measured in the psi rest frame, with z axis equal to the momentum direction of the psi in the gamma-proton frame.
	//so boost!
	PePlus.Boost(-(Ppsi.BoostVector()));
	PeMinus.Boost(-(Ppsi.BoostVector()));
	thetaProd=PeMinus.Theta();
	phiProd=PeMinus.Phi();

	if ((helicity==1)&&(m_helicity_target==1)&&(m_helicity_recoil==1)){
		ampP = one*(m_couplingFp*m_couplingIp);
		ampM = one*(m_couplingFm*m_couplingIp);

		ampP=ampP*(one*cos(phiProd/2)+i*sin(phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*(one*cos(phiProd/2)-i*sin(phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));

		ampP=ampP*(3*cos(thetaProd)-1)*cos(thetaProd/2)*0.5;
		ampM=ampM*sqrt(3.)*(1-cos(thetaProd))*cos(thetaProd/2)*0.5;
	}

	else if ((helicity==-1)&&(m_helicity_target==1)&&(m_helicity_recoil==1)){
		ampP = one*(m_couplingFp*m_couplingIm);
		ampM = one*(m_couplingFm*m_couplingIm);

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));

		ampP=ampP*(one*cos(phiProd/2)-i*sin(phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));

		ampP=ampP*cos(thetaProd/2)*sin(thetaProd/2)*sin(thetaProd/2);
		ampM=ampM*cos(thetaProd/2)*cos(thetaProd/2)*cos(thetaProd/2);
	}

	else if ((helicity==1)&&(m_helicity_target==-1)&&(m_helicity_recoil==1)){
		ampP = one*(m_couplingFp*m_couplingIp);
		ampM = one*(m_couplingFm*m_couplingIp);

		ampP=ampP*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));


		ampP=ampP*cos(thetaProd/2)*cos(thetaProd/2)*sin(thetaProd/2);
		ampM=ampM*sin(thetaProd/2)*sin(thetaProd/2)*sin(thetaProd/2);
	}

	else if ((helicity==-1)&&(m_helicity_target==-1)&&(m_helicity_recoil==1)){
		ampP = one*(m_couplingFp*m_couplingIm);
		ampM = one*(m_couplingFm*m_couplingIm);

		ampP=ampP*(one*cos(phiProd/2)-i*sin(phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)-i*sin(phiProd/2));

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*(1+3*cos(thetaProd))*sin(thetaProd/2)*(-0.5);
		ampM=ampM*sin(thetaProd/2)*cos(thetaProd/2)*cos(thetaProd/2)*sqrt(3.);
	}

	else if ((helicity==1)&&(m_helicity_target==1)&&(m_helicity_recoil==-1)){
		ampP = one*(m_couplingFp*m_couplingIp);
		ampM = one*(m_couplingFm*m_couplingIp);

		ampP=ampP*(one*cos(phiProd/2)+i*sin(phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*(one*cos(phiProd/2)-i*sin(phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));

		ampP=ampP*cos(thetaProd/2)*cos(thetaProd/2)*sin(thetaProd/2)*(-sqrt(3.));
		ampM=ampM*(1+3*cos(thetaProd))*sin(thetaProd/2)*0.5;
	}

	else if ((helicity==-1)&&(m_helicity_target==1)&&(m_helicity_recoil==-1)){
		ampP = one*(m_couplingFp*m_couplingIm);
		ampM = one*(m_couplingFm*m_couplingIm);

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*(one*cos(phiProd/2)-i*sin(phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));


		ampP=ampP*sin(thetaProd/2)*sin(thetaProd/2)*sin(thetaProd/2)*(-1.);
		ampM=ampM*sin(thetaProd/2)*cos(thetaProd/2)*cos(thetaProd/2)*(-sqrt(3.));
	}

	else if ((helicity==1)&&(m_helicity_target==-1)&&(m_helicity_recoil==-1)){
		ampP = one*(m_couplingFp*m_couplingIp);
		ampM = one*(m_couplingFm*m_couplingIp);

		ampP=ampP*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(3*phiProd/2)+i*sin(3*phiProd/2));

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*cos(thetaProd/2)*cos(thetaProd/2)*cos(thetaProd/2);
		ampM=ampM*sin(thetaProd/2)*sin(thetaProd/2)*cos(thetaProd/2)*(sqrt(3.));
	}

	else if ((helicity==-1)&&(m_helicity_target==-1)&&(m_helicity_recoil==-1)){
		ampP = one*(m_couplingFp*m_couplingIm);
		ampM = one*(m_couplingFm*m_couplingIm);

		ampP=ampP*(one*cos(phiProd/2)-i*sin(phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)-i*sin(phiProd/2));

		ampP=ampP*(one*cos(3*phiProd/2)-i*sin(3*phiProd/2));
		ampM=ampM*(one*cos(phiProd/2)+i*sin(phiProd/2));

		ampP=ampP*cos(thetaProd/2)*sin(thetaProd/2)*sin(thetaProd/2)*(sqrt(3));
		ampM=ampM*cos(thetaProd/2)*(3*cos(thetaProd)-1)*0.5;
	}

	ampDecayP=(one*cos(phiDecay)+i*sin(phiDecay));
	ampDecayM=(one*cos(phiDecay)-i*sin(phiDecay));

	ampDecayP=ampDecayP*(one*cos(phiDecay)-i*(1.*m_deltaHelicity_leptons*sin(phiDecay)));
	ampDecayM=ampDecayM*(one*cos(phiDecay)-i*(1.*m_deltaHelicity_leptons*sin(phiDecay)));

	if (m_deltaHelicity_leptons==1){
		ampDecayP=ampDecayP*((1+cos(thetaDecay))/2);
		ampDecayM=ampDecayM*((1-cos(thetaDecay))/2);
	}
	else{
		ampDecayP=ampDecayP*((1-cos(thetaDecay))/2);
		ampDecayM=ampDecayM*((1+cos(thetaDecay))/2);
	}




	amp=(ampP*ampDecayP+ampM*ampDecayM)*4.*2.714E-2; //the last term is the (e/f) factor in the VMD model
	return amp;
}





#ifdef GPU_ACCELERATION 
void
Constant::launchGPUKernel( dim3 dimGrid, dim3 dimBlock, GPU_AMP_PROTO ) const {

	// use integers to endcode the string of daughters -- one index in each
	// decimal place

	GPUResonance_exec( dimGrid,  dimBlock, GPU_AMP_ARGS,int helicity_beam,int helicity_electron,int helicity_target,int helicity_recoil);

}
#endif //GPU_ACCELERATION

Resonance*
Resonance::newAmplitude(const vector < string > & args) const {
	return new Resonance(args);
}

Resonance*
Resonance::clone() const {
	return ( isDefault() ? new Resonance() :
			new Resonance(m_params) );

}
