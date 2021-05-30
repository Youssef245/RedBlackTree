package RBTree;

import java.awt.Color;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;

import javax.swing.JPanel;


public class RBT_Panel extends JPanel {
	
	RedBlackTree rbTree = new RedBlackTree ();
	private int radius = 25;
	private int yoffset = 60;
	private Color text = new Color (255,255,255);
	
	public RBT_Panel (RedBlackTree rbTree) {
		this.rbTree = rbTree;
	}
	public boolean search;
	public int key;
	
	
	public void setKey(int key) {
		this.key = key;
	}

	public void setSearch(boolean search) {
		this.search = search;
	}

	int getGap ()
	{
		int depth=rbTree.getDepth(rbTree.getRoot());
		int multiplier = 30;
		float exponent = (float) 1.4;
		
		if (depth > 6) {
			multiplier += depth * 3;
			exponent += .1;
		}
			
		return (int) Math.pow(depth, exponent) * multiplier;
	}
	
	private void join(Graphics2D graphics, int x1, int y1, int x2, int y2) {
		double hypot = Math.hypot(yoffset, x2 - x1);
		int x11 = (int) (x1 + radius * (x2 - x1) / hypot);
		int y11 = (int) (y1 - radius * yoffset / hypot);
		int x21 = (int) (x2 - radius * (x2 - x1) / hypot);
		int y21 = (int) (y2 + radius * yoffset / hypot);
		graphics.drawLine(x11, y11, x21, y21);
	}
	
	private void drawText (Graphics2D graphics,String number,int x , int y)
	{
		FontMetrics fm = graphics.getFontMetrics();
		double t_width = fm.getStringBounds(number, graphics).getWidth();
		graphics.drawString(number, (int) (x - t_width / 2),
				(int) (y + fm.getMaxAscent() / 2));
	}
	 
	public void drawNode (Graphics2D graphics,Node node,int x, int y)
	{
		if(node.color==1)
			graphics.setColor(Color.red);
		else if (node.color==0)
			graphics.setColor(Color.black);
		graphics.fillOval(x - radius, y - radius, 2 * radius, 2 * radius);
		graphics.setColor(text);
		String number = Integer.toString(node.data);
		drawText(graphics, number, x, y);
		graphics.setColor(Color.GRAY);
	}
	private void drawHallo(Graphics2D graphics  , int x , int y)
	{
		graphics.setColor(Color.green);
		radius += 5;
		graphics.fillOval(x - radius, y - radius, 2 * radius, 2 * radius);
		radius -= 5;
	}
	
	private void paintRBTree (Graphics2D graphics, Node root, int x, int y,int xoffset)
	{
		if(search&&root.data==key)
			drawHallo(graphics, x, y);
		if(root!=null) {
			drawNode(graphics, root, x, y);
			if(root.left!=null)
			{
				join(graphics, x - xoffset, y + yoffset, x, y);
				paintRBTree(graphics, root.left, x - xoffset, y + yoffset,xoffset / 2);
			}
			if(root.right!=null)
			{
				join(graphics, x + xoffset, y + yoffset, x, y);
				paintRBTree(graphics, root.right, x + xoffset, y + yoffset,xoffset / 2);
			}
		}
	}
	
	public void paint (Graphics grahpics)
	{
		if (rbTree.is_empty())
			return;

		Graphics2D graphics2d = (Graphics2D) grahpics;
		graphics2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		graphics2d.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,
				RenderingHints.VALUE_TEXT_ANTIALIAS_ON);

		paintRBTree(graphics2d, rbTree.getRoot(), getWidth() / 2, 30,
				getGap());
	}
	
	
	
	

}
