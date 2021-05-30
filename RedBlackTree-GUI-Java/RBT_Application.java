package RBTree;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * 
 * The GUI Runs Properly when Resizing the Frame after Every Modification.
 * 
 * 
 * */





public class RBT_Application extends JPanel {
	
	RedBlackTree rbTree = new RedBlackTree ();
	RBT_Panel TPanel = new RBT_Panel(rbTree);
	
	public RBT_Application () {
		TPanel.setBackground(new Color(235, 225, 240));	
		setUpPage();
	}
	
	private void setMidPoint(JScrollPane scrollPane) {
		scrollPane.getViewport().setViewPosition(new Point(4100, 0));

	}
	
	private void setTopPanel () {
		JTextField insertField = new JTextField(10);
		JButton insertButton = new JButton("Insert");
		
		JTextField deleteField = new JTextField(10);
		JButton deleteButton = new JButton("Delete");
		
		JTextField searchField = new JTextField(10);
		JButton searchButton = new JButton("Search");
		
		JButton clearButton = new JButton("Clear");
		
		JPanel panel = new JPanel();
		
		panel.add(insertField);
		panel.add(insertButton);
		panel.add(deleteField);
		panel.add(deleteButton);
		panel.add(searchField);
		panel.add(searchButton);
		panel.add(clearButton);
		
		panel.setBackground(Color.WHITE);
		add(panel, BorderLayout.NORTH);
		
		insertButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent actionEvent) {
				if(insertField.getText().equalsIgnoreCase(""))
					return;
				int num = Integer.parseInt(insertField.getText());
				rbTree.insert(num);
				TPanel.repaint();
				insertField.requestFocus();
				insertField.selectAll();
			}

		});
		
		deleteButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent actionEvent) {
				if(deleteField.getText().equalsIgnoreCase(""))
					return;
				int num = Integer.parseInt(deleteField.getText());
				rbTree.deleteNode(num);
				TPanel.repaint();
				deleteField.requestFocus();
				deleteField.selectAll();
			}

		});
		
		searchButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent actionEvent) {
				if(searchField.getText().equalsIgnoreCase(""))
					return;
				int num = Integer.parseInt(searchField.getText());
				Node node;
				node=rbTree.searchTree(num);
				if(node.data!=0) {
					TPanel.setSearch(true);
					TPanel.setKey(num);}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Number Not Found");
				}
				TPanel.repaint();
				searchField.requestFocus();
				searchField.selectAll();
			}

		});
		
		clearButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent actionEvent) {
				rbTree.clear();
				TPanel.repaint();
				deleteField.requestFocus();
				deleteField.selectAll();
			}

		});
			
		
	}
	
	private void setScrollPane() {
		TPanel.setPreferredSize(new Dimension(9000, 4096));

		JScrollPane scroll = new JScrollPane();
		scroll.setViewportView(TPanel);
		scroll.setPreferredSize(new Dimension(750, 500));
		setMidPoint(scroll);
		add(scroll, BorderLayout.CENTER);
	}
	
	private void setUpPage() {
		super.setLayout(new BorderLayout());
		setTopPanel();
		setScrollPane();
	}
	
	
	public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException {
		
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		JFrame frame = new JFrame();
		frame.setTitle("Red Black Tree GUI");
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(new RBT_Application());
		frame.pack();
		frame.setVisible(true);
		
		
	}
	
	

}
