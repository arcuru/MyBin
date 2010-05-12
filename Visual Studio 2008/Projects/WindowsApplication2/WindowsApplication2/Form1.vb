Imports Microsoft.Win32

Public Class Form1

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim DCOM As RegistryKey
        DCOM = Registry.LocalMachine.OpenSubKey("SOFTWARE\Microsoft\Ole", True)
        DCOM.SetValue("EnableDCOM", "Y")
        Label1.Text = DCOM.GetValue("EnableDCOM")

    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim DCOM As RegistryKey
        DCOM = Registry.LocalMachine.OpenSubKey("SOFTWARE\Microsoft\Ole", True)
        DCOM.SetValue("EnableDCOM", "N")
        Label1.Text = DCOM.GetValue("EnableDCOM")
    End Sub
End Class
