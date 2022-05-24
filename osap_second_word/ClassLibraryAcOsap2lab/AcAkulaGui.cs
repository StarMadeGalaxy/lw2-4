using System;
using System.Windows.Forms;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.Runtime;



namespace ClassLibraryAcOsap2lab
{
    public partial class AcAkulaGui : Form
    {
        Gearwheel gearwheel = new Gearwheel();

        public AcAkulaGui()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        // draw gearwheel
        private void button3_Click(object sender, EventArgs e)
        {
            Document doc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Database db = doc.Database;

            if (gearwheel.inner_radius >= gearwheel.outer_radius)
            {
                MessageBox.Show("Outer radius less or equal to inner!", "Radius Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (gearwheel.type == gearwheel_type.none)
            {
                MessageBox.Show("Choose a teeth type!", "Teeth type Error", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            using (Transaction tr = db.TransactionManager.StartTransaction())
            {
                doc.LockDocument();
                BlockTable bt = tr.GetObject(db.BlockTableId, OpenMode.ForRead) as BlockTable;
                BlockTableRecord btr = tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord;
                doc.Editor.WriteMessage("\nDrawing teeth.\n");

                gearwheel.teeth_number = Math.Ceiling(Math.Floor(2 * Math.PI * gearwheel.inner_radius /
                        gearwheel.teeth_width) / 2);

                Point3d centerPt = new Point3d(gearwheel.x_coord, gearwheel.y_coord, 0.0);

                double teeth_angle = 2 * Math.Asin(gearwheel.teeth_width / (2 * gearwheel.inner_radius));
                double arc_angle = (2 * Math.PI - teeth_angle * gearwheel.teeth_number) / gearwheel.teeth_number;
                double start_angle = Math.PI / 2 + teeth_angle / 2;
                double end_angle = start_angle + arc_angle;

                Arc arc = new Arc(centerPt, gearwheel.inner_radius, start_angle, end_angle);
                arc.SetDatabaseDefaults();
                btr.AppendEntity(arc);
                tr.AddNewlyCreatedDBObject(arc, true);

                int arc_number = 1;

                while (arc_number < gearwheel.teeth_number)
                {
                    Arc arc_arr_obj = new Arc(centerPt, gearwheel.inner_radius, start_angle + arc_number * (arc_angle + teeth_angle),
                        end_angle + arc_number * (arc_angle + teeth_angle));
                    btr.AppendEntity(arc_arr_obj);
                    tr.AddNewlyCreatedDBObject(arc_arr_obj, true);
                    arc_number++;
                }

                if (gearwheel.type == gearwheel_type.picked)
                {
                    double limit_teeth_width = 2 * gearwheel.inner_radius * Math.Sqrt(1 - gearwheel.inner_radius * gearwheel.inner_radius /
                        (gearwheel.outer_radius * gearwheel.outer_radius));

                    if (gearwheel.teeth_width > limit_teeth_width)
                    {
                        MessageBox.Show("Width limit reached!", "Limit Error",
                            MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    Polyline teeth = new Polyline();
                    teeth.SetDatabaseDefaults();

                    double x1 = gearwheel.x_coord - gearwheel.teeth_width / 2;
                    double y1 = gearwheel.y_coord + Math.Sqrt((gearwheel.inner_radius * gearwheel.inner_radius) -
                        (gearwheel.teeth_width * gearwheel.teeth_width / 4));

                    Point2d first_point = new Point2d(x1, y1);

                    double x2 = gearwheel.x_coord;
                    double y2 = gearwheel.y_coord + gearwheel.outer_radius;

                    Point2d second_point = new Point2d(x2, y2);

                    double x3 = gearwheel.x_coord + gearwheel.teeth_width / 2;
                    double y3 = y1;

                    Point2d third_point = new Point2d(x3, y3);

                    teeth.AddVertexAt(0, first_point, 0.0, 0.0, 0.0);
                    teeth.AddVertexAt(1, second_point, 0.0, 0.0, 0.0);
                    teeth.AddVertexAt(2, third_point, 0.0, 0.0, 0.0);

                    string str_point = Convert.ToString(gearwheel.x_coord) +
                        "," + Convert.ToString(gearwheel.y_coord);
                    string str_teeth_number = Convert.ToString(gearwheel.teeth_number);
                    string apcom = "_arraypolar _last  " + str_point + " _items " + str_teeth_number + "  ";
                    doc.SendStringToExecute(apcom, true, false, false);

                    doc.Editor.WriteMessage("\n" + apcom + "\n");

                    btr.AppendEntity(teeth);
                    tr.AddNewlyCreatedDBObject(teeth, true);
                }
                else if (gearwheel.type == gearwheel_type.flat)
                {
                    double limit_teeth_width = 2 * Math.Sqrt(gearwheel.outer_radius * gearwheel.outer_radius -
                    gearwheel.inner_radius * gearwheel.inner_radius);

                    if (gearwheel.teeth_width > limit_teeth_width || gearwheel.teeth_width > 2 * gearwheel.inner_radius)
                    {
                        MessageBox.Show("Width limit reached!", "Limit Error",
                            MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    Polyline teeth = new Polyline();
                    teeth.SetDatabaseDefaults();

                    double x1 = gearwheel.x_coord - gearwheel.teeth_width / 2;
                    double y1 = gearwheel.y_coord + Math.Sqrt((gearwheel.inner_radius * gearwheel.inner_radius) -
                        (gearwheel.teeth_width * gearwheel.teeth_width / 4));

                    Point2d first_point = new Point2d(x1, y1);

                    double x2 = x1;
                    double y2 = gearwheel.y_coord + Math.Sqrt((gearwheel.outer_radius * gearwheel.outer_radius) -
                        (gearwheel.teeth_width * gearwheel.teeth_width / 4));

                    Point2d second_point = new Point2d(x2, y2);

                    double x3 = gearwheel.x_coord + gearwheel.teeth_width / 2;
                    double y3 = y2;

                    Point2d third_point = new Point2d(x3, y3);

                    double x4 = x3;
                    double y4 = y1;

                    Point2d fourth_point = new Point2d(x4, y4);

                    teeth.AddVertexAt(0, first_point, 0.0, 0.0, 0.0);
                    teeth.AddVertexAt(1, second_point, 0.0, 0.0, 0.0);
                    teeth.AddVertexAt(2, third_point, 0.0, 0.0, 0.0);
                    teeth.AddVertexAt(3, fourth_point, 0.0, 0.0, 0.0);

                    string str_point = Convert.ToString(gearwheel.x_coord) +
                        "," + Convert.ToString(gearwheel.y_coord);
                    string str_teeth_number = Convert.ToString(gearwheel.teeth_number);
                    string apcom = "_arraypolar _last  " + str_point + " _items " + str_teeth_number + "  ";
                    doc.SendStringToExecute(apcom, true, false, false);

                    doc.Editor.WriteMessage(apcom);

                    btr.AppendEntity(teeth);
                    tr.AddNewlyCreatedDBObject(teeth, true);
                }
                //Point3d centerPt = new Point3d(gearwheel.x_coord, gearwheel.y_coord, 0.0);

                //double teeth_angle = 2 * Math.Asin(gearwheel.teeth_width / (2 * gearwheel.inner_radius));
                //double arc_angle = (2 * Math.PI - teeth_angle * gearwheel.teeth_number) / gearwheel.teeth_number;
                //double start_angle = Math.PI / 2 + teeth_angle / 2;
                //double end_angle = start_angle + arc_angle;

                //Arc arc = new Arc(centerPt, gearwheel.inner_radius, start_angle, end_angle);
                //arc.SetDatabaseDefaults();
                //btr.AppendEntity(arc);
                //tr.AddNewlyCreatedDBObject(arc, true);

                //int arc_number = 1;

                //while (arc_number < gearwheel.teeth_number)
                //{
                //    Entity arc_ent_clone = arc.Clone() as Entity;
                //    Arc arc_arr_obj = arc_ent_clone as Arc;
                //    arc_arr_obj.StartAngle += arc_number * (arc_angle + teeth_angle);
                //    arc_arr_obj.EndAngle += arc_number * (arc_angle + teeth_angle);
                //    btr.AppendEntity(arc_ent_clone);
                //    tr.AddNewlyCreatedDBObject(arc_ent_clone, true);  
                //    arc_number++;
                //}

                tr.Commit();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            gearwheel.x_coord = Convert.ToDouble(textBox1.Text);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            gearwheel.y_coord = Convert.ToDouble(textBox2.Text);
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            gearwheel.inner_radius = Convert.ToDouble(textBox3.Text);
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            gearwheel.outer_radius = Convert.ToDouble(textBox4.Text);
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            gearwheel.teeth_width = Convert.ToDouble(textBox5.Text);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Document Adoc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Database db = Adoc.Database;
            Editor edt = Adoc.Editor;
            Point3d point;

            WindowState = FormWindowState.Minimized;

            PromptPointResult result = edt.GetPoint("Choose a point :");
            if (result.Status == PromptStatus.OK)
            {
                using (Transaction trans = db.TransactionManager.StartTransaction())
                {
                    point = result.Value;
                    //Object.point = point;
                    textBox1.Text = Convert.ToString(point.X);
                    textBox2.Text = Convert.ToString(point.Y);
                    trans.Commit();
                }
            }

            WindowState = FormWindowState.Normal;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //ColorDialog colorDlg = new ColorDialog();

            //if (colorDlg.ShowDialog() == DialogResult.OK)
            //{
            //    panel1.BackColor = colorDlg.Color;
            //    gearwheel.gearwheel_color = colorDlg.Color;
            //}

            Document acDoc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Autodesk.AutoCAD.Windows.ColorDialog dlg = new Autodesk.AutoCAD.Windows.ColorDialog();
            DialogResult dr = dlg.ShowDialog();
            if (dr == DialogResult.OK)
            {
                Autodesk.AutoCAD.Colors.Color acadClr = dlg.Color;
                System.Drawing.Color winClr = new System.Drawing.Color();

                if (dlg.Color.IsByColor)
                {
                    winClr = System.Drawing.Color.FromArgb(acadClr.Red, acadClr.Green, acadClr.Blue); ;
                }
                else if (dlg.Color.IsByAci) // color set by aci
                {
                    // get rgb
                    byte byt = System.Convert.ToByte(acadClr.ColorIndex);
                    int rgb = Autodesk.AutoCAD.Colors.EntityColor.LookUpRgb(byt);
                    long b = (rgb & 0xffL);
                    long g = (rgb & 0xff00L) >> 8;
                    long r = rgb >> 16;
                    winClr = System.Drawing.Color.FromArgb((int)r, (int)g, (int)b);
                }

                panel1.BackColor = winClr;
                acDoc.LockDocument();
                acDoc.Database.Cecolor = acadClr;
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            gearwheel.type = gearwheel_type.picked;

            pictureBox2.BackColor = System.Drawing.Color.Red;

            if (pictureBox1.BackColor == System.Drawing.Color.Red)
                pictureBox1.BackColor = System.Drawing.Color.Transparent;
        }

        private void pictureBoxFlatTeeth_Click(object sender, EventArgs e)
        {
            gearwheel.type = gearwheel_type.flat;

            pictureBox1.BackColor = System.Drawing.Color.Red;
            
            if (pictureBox2.BackColor == System.Drawing.Color.Red)
                pictureBox2.BackColor = System.Drawing.Color.Transparent;

        }

        private void button4_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void AcAkulaGui_Load(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            textBox1.Text = "10";
            textBox2.Text = "10";
            textBox3.Text = "20";
            textBox4.Text = "30";
            textBox5.Text = "5";

            gearwheel.type = gearwheel_type.flat;
            pictureBox1.BackColor = System.Drawing.Color.Red;

            if (pictureBox2.BackColor == System.Drawing.Color.Red)
                pictureBox2.BackColor = System.Drawing.Color.Transparent;
        }
    }
}
