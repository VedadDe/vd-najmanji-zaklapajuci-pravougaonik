object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Form4'
  ClientHeight = 598
  ClientWidth = 1020
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Slika: TImage
    Left = 0
    Top = 8
    Width = 865
    Height = 537
    OnMouseDown = SlikaMouseDown
    OnMouseMove = SlikaMouseMove
  end
  object LabelaBrojTacaka: TLabel
    Left = 890
    Top = 8
    Width = 58
    Height = 13
    Caption = 'Broj tacaka:'
  end
  object Akcija: TLabel
    Left = 888
    Top = 112
    Width = 32
    Height = 13
    Caption = 'Akcija:'
  end
  object Koordinate: TEdit
    Left = 859
    Top = 569
    Width = 121
    Height = 21
    Alignment = taCenter
    TabOrder = 0
    Text = '( 0 , 0 )'
  end
  object EditBrojTacaka: TEdit
    Left = 954
    Top = 8
    Width = 58
    Height = 21
    TabOrder = 1
    Text = '100'
  end
  object GenerisanjeTacaka: TButton
    Left = 888
    Top = 56
    Width = 75
    Height = 25
    Caption = 'Generisi tacke'
    TabOrder = 2
    OnClick = GenerisanjeTacakaClick
  end
  object CrtanjeMnogougla: TRadioButton
    Left = 880
    Top = 144
    Width = 113
    Height = 17
    Caption = 'Crtanje mnogougla'
    TabOrder = 3
  end
  object TackaUnutar: TRadioButton
    Left = 880
    Top = 167
    Width = 132
    Height = 17
    Caption = 'Tacka unutar mnogougla'
    TabOrder = 4
  end
  object DodavanjeTacaka: TRadioButton
    Left = 880
    Top = 190
    Width = 113
    Height = 17
    Caption = 'Dodavanje tacaka'
    TabOrder = 5
  end
  object UnutarKonveksnog: TRadioButton
    Left = 880
    Top = 213
    Width = 113
    Height = 17
    Caption = 'Unutar konveksnog'
    TabOrder = 6
  end
  object ZavrsiMnogougao: TButton
    Left = 888
    Top = 528
    Width = 105
    Height = 25
    Caption = 'Zavrsi mnogougao'
    TabOrder = 7
    OnClick = ZavrsiMnogougaoClick
  end
  object ProstiMnogougao: TButton
    Left = 8
    Top = 565
    Width = 97
    Height = 25
    Caption = 'Prosti mnogougao'
    TabOrder = 8
    OnClick = ProstiMnogougaoClick
  end
  object UvijanjePoklonaDugme: TButton
    Left = 120
    Top = 565
    Width = 97
    Height = 25
    Caption = 'Uvijanje poklona '
    TabOrder = 9
    OnClick = UvijanjePoklonaDugmeClick
  end
  object GrahamScanDugme: TButton
    Left = 232
    Top = 565
    Width = 75
    Height = 25
    Caption = 'Graham scan'
    TabOrder = 10
    OnClick = GrahamScanDugmeClick
  end
  object TangenteDugme: TRadioButton
    Left = 880
    Top = 236
    Width = 113
    Height = 17
    Caption = 'Povlacenje tangenti'
    TabOrder = 11
  end
  object KonveksniInduktivno: TButton
    Left = 320
    Top = 565
    Width = 121
    Height = 25
    Caption = 'Konveksni induktivno'
    TabOrder = 12
    OnClick = KonveksniInduktivnoClick
  end
  object Triangulacija: TButton
    Left = 447
    Top = 565
    Width = 75
    Height = 25
    Caption = 'Triangulacija'
    TabOrder = 13
    OnClick = TriangulacijaClick
  end
  object Button1: TButton
    Left = 896
    Top = 336
    Width = 75
    Height = 25
    Caption = 'NadjiUparivanje'
    TabOrder = 14
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 896
    Top = 408
    Width = 116
    Height = 33
    Caption = 'Triangulacija uz uslov'
    TabOrder = 15
    OnClick = Button2Click
  end
end
