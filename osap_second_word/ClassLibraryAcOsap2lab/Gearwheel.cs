using Autodesk.AutoCAD.Runtime;
using System.Drawing;


namespace ClassLibraryAcOsap2lab
{
    public enum gearwheel_type{
        flat, picked, none
    }

    public class Gearwheel
    {
        public double x_coord;
        public double y_coord;
        public double inner_radius;
        public double outer_radius;
        public double teeth_number;
        public double teeth_length;
        public double teeth_width;
        public Color gearwheel_color;
        public gearwheel_type type;

        public Gearwheel()
        {
            x_coord = 0;
            y_coord = 0;
            inner_radius = 0;
            outer_radius = 0;
            teeth_number = 0;
            teeth_length = 0;
            teeth_width = 0;
            gearwheel_color = Color.White;
            type = gearwheel_type.none;
        }

        [CommandMethod("teethdraw")]
        public void teethdraw()
        {
            AcAkulaGui form = new AcAkulaGui();
            form.Show();
        }
    }
}
