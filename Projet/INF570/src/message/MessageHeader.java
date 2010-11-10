package message;

/**
 * @author Julio
 *
 */
public class MessageHeader {
	private short[] header;

	public MessageHeader(short[] id,TypeMessage type,int ttl, int hops, short[] payloadLength){
		header = new short[23];
		setMessageID(id);
		setTypeMessage(type);
		setTTL(ttl);
		setHops(hops);
		setPayloadLength(payloadLength);
	}
	
	/**
	 * ce constructeur est � utiliser pour la lecture d'un message
	 * @param s
	 */
	public MessageHeader(short [] s){
			if (s.length != 23) {
				System.err.println("Format de header non valide");
				header = null;
			}
			header = s;
	}


	public short[] getHeader(){
		return header;
	}
	
	/**
	 * 
	 * @return L'identifiant du message
	 */
	public short[] getMessageID() {
		short[] s = new short[16];
		for (int i = 0; i <16;i++){
			s[i]=header[i];
		}
		return s;
	}
	/**
	 * 
	 * @return Le type du message
	 */
	public TypeMessage getMessageType() {
		switch (header[16]) {
		case 0:
			return TypeMessage.PING;
		case 1:
			return TypeMessage.PONG;
		case 64:
			return TypeMessage.PUSH;
		case 128:
			return TypeMessage.QUERY;
		case 129:
			return TypeMessage.QUERY_HIT;
		default:
			break;
		}
		return null;

	}
	/**
	 * 
	 * @return Le TTL
	 */
	public int getTTL() {
		return header[17];
	}
	/**
	 * 
	 * @return Le Hops
	 */
	public int getHops() {
		return header[18];
	}
	/**
	 * 
	 * @return La taille du message
	 */
	public short[] getPayloadLength() {
		short[] s = new short[4];
		for (int i = 0; i <4;i++){
			s[i]=header[i+19];
		}
		return s;
	}

	private void setMessageID(short[] s){
		for (int i = 0; i <16;i++){
			header[i]=s[i];
		}
	}
	private void setTypeMessage(TypeMessage t){
		switch (t) {
		case PING:
			header[16] = 0;
			break;
		case PONG:
			header[16] = 1;
			break;
		case PUSH:
			header[16] = 64;
			break;
		case QUERY:
			header[16] = 128;
			break;
		case QUERY_HIT:
			header[16] = 129;
			break;

		default:
			break;
		}
	}
	private void setTTL(int i) {
		header[17] = (short) i;
	}
	private void setHops(int i) {
		header[18] = (short) i;
	}
	private void setPayloadLength(short[] s) {
		for (int i = 0; i <4;i++){
			header[i+19]=s[i];
		}
	}
	
	private static short[] subTab(short[] t,int i, int j){
		short[] tab = new short[j-i+1];
		for(int k = i;k<j+1;k++){
			tab[k-i] = t[k];
		}
		return tab;
	}
	
	/**
	 * � appeler lors de la lecture d'un message apr�s avois analys� le header
	 * 
	 * @param h
	 * @param payload
	 * @return	un message de type coh�rent avec le header (null sinon)
	 */
	public static Message parseMessage(MessageHeader h,short[] payload){
		switch (h.getMessageType()) {
		case PING:
			if (payload!=null) {
				System.err.println("payload et header incoh�rents");
				return null;
			}
			return new Ping(h.getMessageID(), h.getTTL(), h.getHops());
		case PONG:
			if (payload.length!=14) {
				System.err.println("payload et header incoh�rents");
				return null;
			}
			return new Pong(h,subTab(payload, 0, 1),subTab(payload, 2, 5),subTab(payload, 6, 9),subTab(payload, 10, 13));
		case PUSH:
			return null;
		case QUERY:
			return null;
		case QUERY_HIT:
			return null;
		default:
			break;
		}
		return null;
	}
	


}
