Public Class Form1
    Dim number1 As Long = 0
    Dim number2 As Long = 0
    Dim total As Long = 0
    Dim operand As String = ""


   
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        txtDisplay.Text = txtDisplay.Text & Button1.Text
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        txtDisplay.Text = txtDisplay.Text & Button2.Text
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        txtDisplay.Text = txtDisplay.Text & Button3.Text
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        txtDisplay.Text = txtDisplay.Text & Button4.Text
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        txtDisplay.Text = txtDisplay.Text & Button5.Text
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        txtDisplay.Text = txtDisplay.Text & Button6.Text
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        txtDisplay.Text = txtDisplay.Text & Button7.Text
    End Sub

    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        txtDisplay.Text = txtDisplay.Text & Button8.Text
    End Sub

    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click
        txtDisplay.Text = txtDisplay.Text & Button9.Text
    End Sub

    Private Sub Button10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button10.Click
        txtDisplay.Text = txtDisplay.Text & Button10.Text
    End Sub

    Private Sub ButtonPlus_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonPlus.Click
        If operand = "" Then
            number1 = txtDisplay.Text
            operand = "+"
            txtDisplay.Text = ""
        End If
    End Sub

    Private Sub ButtonMin_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonMin.Click
        If operand = "" Then
            number1 = txtDisplay.Text
            operand = "-"
            txtDisplay.Text = ""
        End If
    End Sub

    Private Sub ButtonMult_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonMult.Click
        If operand = "" Then
            number1 = txtDisplay.Text
            operand = "*"
            txtDisplay.Text = ""
        End If
    End Sub

    Private Sub ButtonDiv_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonDiv.Click
        If operand = "" Then
            number1 = txtDisplay.Text
            operand = "/"
            txtDisplay.Text = ""
        End If
    End Sub

    Private Sub ButtonEq_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonEq.Click
        If operand = "+" Then
            number2 = txtDisplay.Text
            total = number1 + number2
            txtDisplay.Text = total
        ElseIf operand = "-" Then
            number2 = txtDisplay.Text
            total = number1 - number2
            txtDisplay.Text = total
        ElseIf operand = "*" Then
            number2 = txtDisplay.Text
            total = number1 * number2
            txtDisplay.Text = total
        ElseIf operand = "/" Then
            number2 = txtDisplay.Text
            total = number1 / number2
            txtDisplay.Text = total
        End If
    End Sub

    Private Sub ButtonCl_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonCl.Click
        txtDisplay.Text = ""
        operand = ""
    End Sub

End Class
