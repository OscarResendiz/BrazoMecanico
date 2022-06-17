VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "puertos"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "enviar"
      Height          =   735
      Left            =   1560
      TabIndex        =   4
      Top             =   1560
      Width           =   1695
   End
   Begin VB.TextBox dato 
      Height          =   375
      Left            =   1800
      TabIndex        =   1
      Top             =   720
      Width           =   1815
   End
   Begin VB.TextBox direccion 
      Height          =   375
      Left            =   1800
      TabIndex        =   0
      Top             =   240
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "dato"
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "direccion"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   240
      Width           =   1095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Dim d, Dire As Byte
d = Val(dato)
Dire = Val(direccion)
outport Dire, d
End Sub

