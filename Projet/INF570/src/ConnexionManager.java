import java.util.HashMap;
import java.util.LinkedList;

/**
 * Contient la liste des connexions et g�re les innondations
 * @author Julio
 *
 */
public class ConnexionManager extends Thread{
	private HashMap<Connexion, Connexion> connexions;
	private HashMap<Connexion, Connexion> preConnexions;
	private LinkedList<Message> toSend;

	

	public ConnexionManager() {
		super();
		this.connexions = new HashMap<Connexion, Connexion>();
		this.toSend = new LinkedList<Message>();
		this.preConnexions = new HashMap<Connexion, Connexion>();
	}
	
	public synchronized void remove(Connexion c){}
	public synchronized void addConnexion(Connexion preConnexion){}


	public synchronized void sendAll(Message m, Connexion exclude){
		
	}
	/**
	 * Extrait le premier message de la file d'envoi de mani�re synchronis�e TODO
	 * @return le message � envoyer
	 */
	private synchronized Message getFirstToSend(){
		return null;
	}
	
	private synchronized void confirmConnexion(Connexion c){
		
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
	}
	
	

}
