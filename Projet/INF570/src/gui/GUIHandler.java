package gui;

import message.Result;

public class GUIHandler implements OutputControler{

	public void printInConsole(String s) {
		FenetrePrincipale.display(s);
	}

	@Override
	public void displayResult(Result[] tab) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void displayVoisin() {
		// TODO Auto-generated method stub
		
	}

}