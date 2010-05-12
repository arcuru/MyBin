Public Class Form1

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Panel1.Visible = False
        Panel2.Visible = False
        RadioButton1.Checked = True
    End Sub

    Private Sub RadioButton1_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RadioButton1.CheckedChanged
        Panel1.Visible = True
        Panel2.Visible = False

    End Sub

    Private Sub RadioButton2_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RadioButton2.CheckedChanged
        Panel2.Visible = True
        Panel1.Visible = False
        System.Diagnostics.Process.Start("http://www.google.com/")
    End Sub
End Class
