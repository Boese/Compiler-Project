using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Gui
{
    public partial class Form1 : Form
    {
        private Random rand;
        private List<Turtle> turtles;
        private List<string> inStr;
        private List<Defined> symbols;
        private bool init;
        private bool penup;
        private int instrCounter;
        public Form1()
        {
            init = true;
            penup = true;
            InitializeComponent();
            DoubleBuffered = true;
            ResizeRedraw = true;
            turtles = new List<Turtle>();
            inStr = new List<string>();
            symbols = new List<Defined>();
            rand = new Random();
            instrCounter = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string line;

            // Read the file and display it line by line.
            System.IO.StreamReader file =
               new System.IO.StreamReader("C:\\Users\\Dustin Falgout\\Documents\\GitHub\\Compiler-Project\\TurtleRDP\\TurtleRDP\\GUIinput.txt");
            while ((line = file.ReadLine()) != null)
            {
                if (line.StartsWith("Define"))
                {
                    symbols.Add(new Defined(line.Split(' ').ElementAt(1)));
                    while ((line = file.ReadLine()) != "End")
                    {
                        symbols.Last().Value.Add(line);
                    }
                    line = file.ReadLine();
                }
                if (line.StartsWith("Call"))
                {
                    foreach (var t in symbols)
                    {
                        if (t.Name == line.Split(' ').ElementAt(1))
                        {
                            foreach (var str in t.Value)
                                inStr.Add(str);
                        }
                    }
                }
                else
                    inStr.Add(line);

            }

            file.Close();

            foreach (var s in inStr)
            {
                codeWindow.Text += s + Environment.NewLine;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                doWork(inStr.ElementAt(instrCounter));
                int temp = codeWindow.GetFirstCharIndexFromLine(instrCounter);
                codeWindow.Select(temp, inStr.ElementAt(instrCounter).Length);
                codeWindow.SelectionBackColor = Color.Yellow;
                instrCounter++;
            }
            catch (Exception)
            {
                button1.Enabled = false;
                MessageBox.Show("Program Complete");
            }
        }

        private void initTurtles(int number)
        {
            for (int i = 0; i < number; i++)
            {
                int x = rand.Next(pictureBox1.Left, pictureBox1.Right - 100);
                int y = rand.Next(pictureBox1.Top, pictureBox1.Bottom - 100);
                turtles.Add(new Turtle(x, y));
            }
        }

        private void setDistance(int dist)
        {
            foreach (Turtle t in turtles)
            {
                t.setDest(dist);
            }
        }

        private void setDirection(int dir)
        {
            foreach (Turtle t in turtles)
            {
                t.setDirection(dir);
            }
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Bitmap img = new Bitmap(Properties.Resources.turtle);
            Color invis = Color.FromArgb(255,255,255);
            img.MakeTransparent(invis);

            Brush brush = new SolidBrush(Color.Red);
            Pen pen = new Pen(brush, 3);

            foreach (Turtle t in turtles)
            {

                Brush turtleBrush = new SolidBrush(t.color);
                if (init)
                {
                    g.DrawImage(img, t.PrevX, t.PrevY, 100, 100);
                    g.DrawImage(t.img, t.PrevX, t.PrevY, 100, 100);
                }
                //g.FillEllipse(turtleBrush, t.PrevX, t.PrevY, 50, 50);
                else
                {
                    Point p1 = new Point((int)t.PrevX + 50, (int)t.PrevY + 50);
                    int x = t.PrevX - t.DestX;
                    int y = t.PrevY - t.DestY;
                    Point p2 = new Point(x + 50, y + 50);
                    g.DrawImage(img, x, y, 100, 100);
                    g.DrawImage(t.img, x, y, 100, 100);
                    //g.FillEllipse(turtleBrush, x, y, 50, 50);
                    if (!penup)
                        g.DrawLine(pen, p1, p2);
                    t.setPrev(x, y);
                }
            }
        }

        private void doWork(string str)
        {
            string tmp = str.Split(' ').First();

            switch(tmp)
            {
                case "Create":
                    initTurtles(Convert.ToInt32(str.Split(' ').ElementAt(1)));
                    pictureBox1.Invalidate();
                    break;
                case "Forward":
                    setDistance(Convert.ToInt32(str.Split(' ').ElementAt(1)));
                    init = false;
                    pictureBox1.Invalidate();
                    break;
                case "Back":
                    setDistance(-1 * Convert.ToInt32(str.Split(' ').ElementAt(1)));
                    init = false;
                    pictureBox1.Invalidate();
                    break;
                case "Right":
                    setDirection(Convert.ToInt32(str.Split(' ').ElementAt(1)));
                    break;
                case "Left":
                    setDirection(-1 * Convert.ToInt32(str.Split(' ').ElementAt(1)));
                    break;
                case "Penup":
                    penup = true;
                    break;
                case "Pendown":
                    penup = false;
                    break;
                case "Setcolor":
                    foreach (Turtle t in turtles)
                    {
                        t.setColor(str.Split(' ').ElementAt(1));
                    }
                    pictureBox1.Invalidate();
                    break;
                case "red":
                case "blue":
                case "black":
                case "green":
                case "yellow":
                case "purple":
                case "pink":
                    foreach (Turtle t in turtles)
                    {
                        if (t.color.Name.ToLower() == tmp)
                        {
                            if (str.Split(' ').ElementAt(2) != "]")
                                t.setColor(str.Split(' ').ElementAt(3));
                        }
                        else
                        {
                            if (str.Split(' ').Length > 7)
                                t.setColor(str.Split(' ').ElementAt(7));
                            else if (str.Split(' ').Length > 5)
                                t.setColor(str.Split(' ').ElementAt(5));
                            else
                                break;
                        }
                    }
                    pictureBox1.Invalidate();
                    break;
            }
        }
    }
}
