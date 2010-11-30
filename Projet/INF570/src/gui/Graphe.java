package gui;

import java.awt.Color;
import java.awt.Graphics;
import java.util.HashMap;
import java.util.LinkedList;

import javax.swing.JPanel;

import config.Settings;
import connexion.Neighbour;

public class Graphe extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int w;
	private int h;
	private LinkedList<Neighbour> nodes;
	private LinkedList<Color> colors;
	
	
	public Graphe(int w, int h) {
		super();
		this.w = w;
		this.h = h;
		this.nodes = new LinkedList<Neighbour>();
		this.colors = new LinkedList<Color>();
		
		int n = Settings.getMaxTTL();
		
		for (int i = 0; i < n; i++) {
			colors.add( new Color((int) (150+100*Math.random()),(int) (150+100*Math.random()),(int) (150+100*Math.random())));
		}
		
	}
	
	public void setNeighbour(LinkedList<Neighbour> n) {
		nodes = n;
		this.paintImmediately(this.getBounds());
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		HashMap<Integer, LinkedList<String>> set = new HashMap<Integer, LinkedList<String>>();
		for (Neighbour nei : nodes) {
			if(!set.containsKey(nei.getDistance()))set.put(nei.getDistance(), new LinkedList<String>());
			set.get(nei.getDistance()).add(nei.getIP());
		}
		int maxR = (int) (w*0.4);
		int disc = set.keySet().size();
		int k = disc;
		for(int i : set.keySet()){
			int r = (int) (k*maxR*1./disc);
			drawDisk(r,colors.get(i), g);
			drawOnDisk(r, set.get(i), g);
			k--;
		}
		
		
		
	}
	
	
	private void drawDisk(int rayon, Color c,Graphics g){
		g.setColor(c);
		g.fillOval((int) (w*1./2-rayon),(int) ( h*1./2-rayon*1./2), 2*rayon, rayon);
		
	}
	
	private void drawOnDisk(int rayon, LinkedList<String> labels,Graphics g){
		g.setColor(new Color(0,0,155));
		int n = labels.size();
		int k = 0;
		for (String string : labels) {
			int x = (int) (w*1./2+rayon*Math.cos(k*2*Math.PI/n));
			int y = (int) (h*1./2+rayon*Math.sin(k*2*Math.PI/n)/2);
			g.fillOval((int) (x-4),(int) (y-4),8, 8);
			g.drawChars(string.toCharArray(), 0, string.length(), x-5*string.length()/2, y-5);
			k++;
		}
		
		
		
	}
	
	
}
