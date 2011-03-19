import Jama.Matrix;
import Jcg.geometry.Point_3;
import Jcg.polyhedron.Vertex;



// Cette classe impl�mente le tenseur de courbure en un point
public class TenseurCourbure {
	
	// Variables
	Vertex<Point_3> point ;
	Matrix kappa ;
	Matrix[] eigenvector ;
	double[] eigenvalue ; // Valeurs propres
	
	// Constructeur
	public TenseurCourbure (Vertex<Point_3> p, Matrix tenseur, Matrix normal, Matrix T1, Matrix T2, double vp1, double vp2)
	{
		point = p ;
		kappa = tenseur ;
		Matrix[] ev = {normal, T1, T2} ;
		eigenvector = ev ;
		double[] array = {0, vp1, vp2} ;
		eigenvalue = array ;
	}
	
	// M�thodes d'acc�s
	public Matrix getTenseur() { return kappa ;}
	public double getEigenvalue(int i) { return eigenvalue[i] ;}
	public Matrix getEigenvector(int i) { return eigenvector[i] ;}
	
}
