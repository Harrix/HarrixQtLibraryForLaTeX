template <class T> QString THQt_LatexShowTwoChartsOfLine (T *VHQt_VectorX,T *VHQt_VectorY1,T *VHQt_VectorY2, int VHQt_N, QString TitleChart, QString NameVectorX, QString NameVectorY,QString NameLine1, QString NameLine2, QString Label,bool ShowLine,bool ShowPoints,bool ShowArea,bool ShowSpecPoints, bool ForNormalSize, bool GrayStyle)
{
    /*
	Функция возвращает строку с выводом некоторых двух графиков за раз по точкам с Latex кодами.
    У обоих графиков одинаковый массив значений X.
    Входные параметры:
     VHQt_VectorX - указатель на вектор координат X точек;
     VHQt_VectorY1 - указатель на вектор координат Y точек первой линии;
     VHQt_VectorY2 - указатель на вектор координат Y точек второй линии;
     VHQt_N - количество точек;
     TitleChart - заголовок графика;
     NameVectorX - название оси Ox. В формате: [обозначение], [расшифровка]. Например: u, Вероятность выбора;
     NameVectorY - название оси Oy. В формате: [обозначение], [расшифровка]. Например: q, Количество абрикосов;
     NameLine1 - название первого графика (для легенды);
     NameLine2 - название второго графика (для легенды);
     Label - label для графика;
     ShowLine - показывать ли линию;
     ShowPoints - показывать ли точки;
     ShowArea - показывать ли закрашенную область под кривой;
     ShowSpecPoints - показывать ли специальные точки;
     ForNormalSize - нормальный размер графика (на всю ширину) или для маленького размера график создается;
     GrayStyle - второй график рисовать серым, а не красным.
    Возвращаемое значение:
     Строка с Latex кодами с выводимым графиком.
    */
    QString VHQt_Result;//переменная итогового результата
    int i,j;

    //посчитаем границы изменения параметров
    T MinX=VHQt_VectorX[0];
    for (int i=1;i<VHQt_N;i++)
        if (VHQt_VectorX[i]<MinX)
            MinX=VHQt_VectorX[i];

    T MinY1=VHQt_VectorY1[0];
    for (int i=1;i<VHQt_N;i++)
        if (VHQt_VectorY1[i]<MinY1)
            MinY1=VHQt_VectorY1[i];

    T MinY2=VHQt_VectorY2[0];
    for (int i=1;i<VHQt_N;i++)
        if (VHQt_VectorY2[i]<MinY2)
            MinY2=VHQt_VectorY2[i];

    T MaxX=VHQt_VectorX[0];
    for (int i=1;i<VHQt_N;i++)
        if (VHQt_VectorX[i]>MaxX)
            MaxX=VHQt_VectorX[i];

    T MaxY1=VHQt_VectorY1[0];
    for (int i=1;i<VHQt_N;i++)
        if (VHQt_VectorY1[i]>MaxY1)
            MaxY1=VHQt_VectorY1[i];

    T MaxY2=VHQt_VectorY2[0];
    for (int i=1;i<VHQt_N;i++)
        if (VHQt_VectorY2[i]>MaxY2)
            MaxY2=VHQt_VectorY2[i];

    T MinY;
    T MaxY;

    if (MinY1<MinY2)
        MinY=MinY1;
    else
        MinY=MinY2;

    if (MaxY1>MaxY2)
        MaxY=MaxY1;
    else
        MaxY=MaxY2;

    T LengthX=MaxX-MinX;
    T LengthY=MaxY-MinY;

    //посчитаем область графика, в которой все будет рисоваться
    T LeftXBoundingBox=MinX-LengthX/15.;
    T LeftYBoundingBox=MinY-LengthY/15.;
    T RightXBoundingBox=MaxX+LengthX/15.;
    T RightYBoundingBox=MaxY+LengthY/15.;

    if (MinX==MaxX) { LeftXBoundingBox-=1; LengthX=2; RightXBoundingBox+=1;}
    if (MinY==MaxY) { LeftYBoundingBox-=1; LengthY=2; RightYBoundingBox+=1;}

    QString SLeftXBoundingBox=QString::number(LeftXBoundingBox);
    QString SLeftYBoundingBox=QString::number(LeftYBoundingBox);
    QString SRightXBoundingBox=QString::number(RightXBoundingBox);
    QString SRightYBoundingBox=QString::number(RightYBoundingBox);
    SLeftXBoundingBox.replace(',', '.');
    SLeftYBoundingBox.replace(',', '.');
    SRightXBoundingBox.replace(',', '.');
    SRightYBoundingBox.replace(',', '.');

    if (ForNormalSize)
        VHQt_Result+="% Вывод графика\n";
    else
        VHQt_Result+="% Вывод подграфика\n";

    //Если график маленький, то дополнительные настройки:
    if (!ForNormalSize)
    {
        VHQt_Result+="{\\pgfplotsset{every axis legend/.append style={at={(0.5,-0.25)},anchor=north,legend cell align=left},}\n";
    }

    //Обработаем текст подписи к осям.
    QString NameVectorXnew=NameVectorX,NameVectorYnew=NameVectorY, subStr;

    subStr=",";
    if (NameVectorXnew.contains(subStr))
        NameVectorXnew="$"+NameVectorXnew.replace(NameVectorXnew.indexOf(subStr), (subStr).size(), "$,");
    if (NameVectorYnew.contains(subStr))
        NameVectorYnew="$"+NameVectorYnew.replace(NameVectorYnew.indexOf(subStr), (subStr).size(), "$,");

    subStr=".";
    if (NameVectorXnew.contains(subStr))
        NameVectorXnew="$"+NameVectorXnew.replace(NameVectorXnew.indexOf(subStr), (subStr).size(), "$,");
    if (NameVectorYnew.contains(subStr))
        NameVectorYnew="$"+NameVectorYnew.replace(NameVectorYnew.indexOf(subStr), (subStr).size(), "$,");

    if ((!NameVectorXnew.contains(","))&&(!NameVectorXnew.contains(".")))
        if (!HQt_CheckRus(NameVectorXnew))
            NameVectorXnew="$"+NameVectorXnew+"$";

    if ((!NameVectorYnew.contains(","))&&(!NameVectorYnew.contains(".")))
        if (!HQt_CheckRus(NameVectorYnew))
            NameVectorYnew="$"+NameVectorYnew+"$";

    NameVectorXnew=NameVectorXnew.replace(";","");
    NameVectorYnew=NameVectorYnew.replace(";","");

    NameVectorXnew=NameVectorXnew.replace("&","\\");
    NameVectorYnew=NameVectorYnew.replace("&","\\");

    //рисуем область графика и оси
    if (ForNormalSize) VHQt_Result+="\\begin{figure} [H]\n";
    if (ForNormalSize) VHQt_Result+="\\centering\n";
    if (ForNormalSize) VHQt_Result+="\\begin{tikzpicture}\n"; else VHQt_Result+="\\begin{tikzpicture}[scale=0.9, baseline]\n";
    VHQt_Result+="\\begin{axis} [\n";
    VHQt_Result+="xlabel={"+NameVectorXnew+"},\n";
    VHQt_Result+="ylabel={"+NameVectorYnew+"},\n";
    //if (ForNormalSize)
    VHQt_Result+="xmax="+SRightXBoundingBox+",\n";
    //if (ForNormalSize)
    VHQt_Result+="ymax="+SRightYBoundingBox+",\n";
    if (ForNormalSize)
    {
        VHQt_Result+="height=10cm,\n";
        VHQt_Result+="width=17cm,\n";
    }
    else
    {
        VHQt_Result+="height=5.8cm,\n";
        VHQt_Result+="width=8.5cm,\n";
    }
    VHQt_Result+="]\n\n";

    //копируем во временный массив наши массивы, чтобы их не потревожить
    T *Temp_VHQt_VectorX=new T[VHQt_N];
    T *Temp_VHQt_VectorY1=new T[VHQt_N];
    T *Temp_VHQt_VectorY2=new T[VHQt_N];
    for (i=0;i<VHQt_N;i++) Temp_VHQt_VectorX[i]=VHQt_VectorX[i];
    for (i=0;i<VHQt_N;i++) Temp_VHQt_VectorY1[i]=VHQt_VectorY1[i];
    for (i=0;i<VHQt_N;i++) Temp_VHQt_VectorY2[i]=VHQt_VectorY2[i];

    //отсортируем массивы
    for(i=VHQt_N-1;i>0;i--)
        for(j=0;j<i;j++)
            if(Temp_VHQt_VectorX[j]>Temp_VHQt_VectorX[j+1])
            {
                T x;
                x=Temp_VHQt_VectorX[j+1];
                Temp_VHQt_VectorX[j+1]=Temp_VHQt_VectorX[j];
                Temp_VHQt_VectorX[j]=x;
                x=Temp_VHQt_VectorY1[j+1];
                Temp_VHQt_VectorY1[j+1]=Temp_VHQt_VectorY1[j];
                Temp_VHQt_VectorY1[j]=x;
                x=Temp_VHQt_VectorY2[j+1];
                Temp_VHQt_VectorY2[j+1]=Temp_VHQt_VectorY2[j];
                Temp_VHQt_VectorY2[j]=x;
            }

    QString SData1;
    for (i=0;i<VHQt_N;i++)
        SData1+=" ("+QString::number(Temp_VHQt_VectorX[i])+", "+QString::number(Temp_VHQt_VectorY1[i])+") \n";

    QString SData2;
    for (i=0;i<VHQt_N;i++)
        SData2+=" ("+QString::number(Temp_VHQt_VectorX[i])+", "+QString::number(Temp_VHQt_VectorY2[i])+") \n";

    QString Plot1,Plot2;

    QString PlotSecond="plotsecond";
    if (GrayStyle) PlotSecond="plotsecondgray";

    if ((ShowArea)&&((ShowPoints)||(ShowLine)))
    {
        //нарисуем закрашенную область
        Plot1+="\\addplot[color=plotmain, draw=none,fill, fill opacity = 0.5,forget plot] coordinates {\n";
        Plot1+=" ("+QString::number(MinX)+", "+QString::number(MinY)+") \n";
        Plot1+=SData1;
        Plot1+=" ("+QString::number(MaxX)+", "+QString::number(MinY)+") \n";
        Plot1+="};\n\n";

        //нарисуем закрашенную область
        Plot2+="\\addplot[color="+PlotSecond+", draw=none,fill, fill opacity = 0.4,forget plot] coordinates {\n";
        Plot2+=" ("+QString::number(MinX)+", "+QString::number(MinY)+") \n";
        Plot2+=SData2;
        Plot2+=" ("+QString::number(MaxX)+", "+QString::number(MinY)+") \n";
        Plot2+="};\n\n";
    }

    if ((ShowArea)&&(!ShowPoints)&&(!ShowLine))
    {
        //нарисуем закрашенную область
        Plot1+="\\addplot[color=plotmain, draw=none,fill, fill opacity = 0.5] coordinates {\n";
        Plot1+=" ("+QString::number(MinX)+", "+QString::number(MinY)+") \n";
        Plot1+=SData1;
        Plot1+=" ("+QString::number(MaxX)+", "+QString::number(MinY)+") \n";
        Plot1+="};\n";
        Plot1+="\\addlegendentry{"+NameLine1+"};\n\n";

        //нарисуем закрашенную область
        Plot2+="\\addplot[color="+PlotSecond+", draw=none,fill, fill opacity = 0.4] coordinates {\n";
        Plot2+=" ("+QString::number(MinX)+", "+QString::number(MinY)+") \n";
        Plot2+=SData2;
        Plot2+=" ("+QString::number(MaxX)+", "+QString::number(MinY)+") \n";
        Plot2+="};\n";
        Plot2+="\\addlegendentry{"+NameLine2+"};\n\n";
    }

    if ((ShowPoints)&&(ShowLine))
    {
        QString MarkSize;
        if (VHQt_N>100) MarkSize=",mark size=1.5pt";

        //Нарисуем график
        Plot1+="\\addplot[color=plotmain, mark=*,mark options={plotmain,opacity = 1, fill=white,thick}"+MarkSize+",very thick] coordinates {\n";
        Plot1+=SData1;
        Plot1+="};\n";
        Plot1+="\\addlegendentry{"+NameLine1+"};\n\n";

        //Нарисуем график
        Plot2+="\\addplot[color="+PlotSecond+", mark=*,mark options={"+PlotSecond+",opacity = 1, fill=white,fill opacity = 1, thick,solid}"+MarkSize+",very thick,dashed] coordinates {\n";
        Plot2+=SData2;
        Plot2+="};\n";
        Plot2+="\\addlegendentry{"+NameLine2+"};\n\n";
    }

    if ((ShowPoints)&&(!ShowLine))
    {
        QString MarkSize;
        if (VHQt_N>100) MarkSize=",mark size=1.5pt";

        //Нарисуем график
        Plot1+="\\addplot[color=plotmain, mark=*,mark options={plotmain,opacity = 1, fill=white,thick}"+MarkSize+",only marks] coordinates {\n";
        Plot1+=SData1;
        Plot1+="};\n";
        Plot1+="\\addlegendentry{"+NameLine1+"};\n\n";

        //Нарисуем график
        Plot2+="\\addplot[color="+PlotSecond+", mark=square*,mark options={"+PlotSecond+",opacity = 1, fill=white,fill opacity = 1, thick,solid}"+MarkSize+",only marks] coordinates {\n";
        Plot2+=SData2;
        Plot2+="};\n";
        Plot2+="\\addlegendentry{"+NameLine2+"};\n\n";
    }

    if ((!ShowPoints)&&(ShowLine))
    {
        Plot1+="\\addplot[color=plotmain, no markers,very thick] coordinates {\n";
        Plot1+=SData1;
        Plot1+="};\n";
        Plot1+="\\addlegendentry{"+NameLine1+"};\n\n";

        Plot2+="\\addplot[color="+PlotSecond+", no markers,very thick] coordinates {\n";
        Plot2+=SData2;
        Plot2+="};\n";
        Plot2+="\\addlegendentry{"+NameLine2+"};\n\n";
    }


    //собираем общий график
    VHQt_Result+=Plot2;
    VHQt_Result+=Plot1;

    if (ShowSpecPoints)
    {
        //Определим что писать в виде min_x и др.
        QString LabelX="Ox",LabelY="Oy";
        if (NameVectorX.length()<100) LabelX=NameVectorX;else LabelX="Ox";
        if (NameVectorY.length()<100) LabelY=NameVectorY;else LabelY="Oy";

        if (LabelX.contains(",")) LabelX=LabelX.mid(0,LabelX.indexOf(","));
        if (LabelY.contains(",")) LabelY=LabelY.mid(0,LabelY.indexOf(","));

        if (LabelX.contains(".")) LabelX=LabelX.mid(0,LabelX.indexOf("."));
        if (LabelY.contains(".")) LabelY=LabelY.mid(0,LabelY.indexOf("."));

        if (HQt_CheckRus(LabelX)) LabelX="Ox";
        if (HQt_CheckRus(LabelY)) LabelY="Oy";

        LabelX=LabelX.replace(";","");
        LabelY=LabelY.replace(";","");

        LabelX=LabelX.replace("&","\\");
        LabelY=LabelY.replace("&","\\");

        //Теперь проставим точки
        //Нулевая точка
        VHQt_Result+="\\addplot [\n";
        VHQt_Result+="black,\n";
        VHQt_Result+="mark = *,\n";
        VHQt_Result+="mark options={plotcoordinate, opacity = 1, fill=white, fill opacity = 1, thin, solid,scale=0.6},\n";
        VHQt_Result+="nodes near coords={$\\min_{"+LabelX+"}="+QString::number(MinX)+"; \\min_{"+LabelY+"}="+QString::number(MinY)+" $},\n";
        VHQt_Result+="every node near coord/.style={black, anchor=south west,font=\\tiny},\n";
        VHQt_Result+="fill=white,\n";
        VHQt_Result+="forget plot\n";
        VHQt_Result+="]\n";
        VHQt_Result+="coordinates {("+QString::number(MinX)+","+QString::number(MinY)+")};\n";

        //Максимальная по Y
        VHQt_Result+="\\addplot [\n";
        VHQt_Result+="black,\n";
        VHQt_Result+="mark = *,\n";
        VHQt_Result+="mark options={plotcoordinate, opacity = 1, fill=white, fill opacity = 1, thin, solid,scale=0.6},\n";
        VHQt_Result+="nodes near coords={$\\max_{"+LabelY+"} = "+QString::number(MaxY)+" $},\n";
        VHQt_Result+="every node near coord/.style={black, anchor=south west,font=\\tiny},\n";
        VHQt_Result+="fill=white,\n";
        VHQt_Result+="forget plot\n";
        VHQt_Result+="] \n";
        VHQt_Result+="coordinates {("+QString::number(MinX)+","+QString::number(MaxY)+")};\n";

        //Максимальная по X
        VHQt_Result+="\\addplot [\n";
        VHQt_Result+="black,\n";
        VHQt_Result+="mark = *,\n";
        VHQt_Result+="mark options={plotcoordinate, opacity = 1, fill=white, fill opacity = 1, thin, solid,scale=0.6},\n";
        VHQt_Result+="nodes near coords={$\\max_{"+LabelX+"} = "+QString::number(MaxX)+" $},\n";
        VHQt_Result+="every node near coord/.style={black, anchor=north west,font=\\tiny, rotate=90},\n";
        VHQt_Result+="fill=white,\n";
        VHQt_Result+="forget plot\n";
        VHQt_Result+="] \n";
        VHQt_Result+="coordinates {("+QString::number(MaxX)+","+QString::number(MinY)+")};\n";
    }

    VHQt_Result+="\\end{axis}\n";
    VHQt_Result+="\\end{tikzpicture}\n";

    if (!ForNormalSize)
    {
        VHQt_Result+="}\n";
    }

    if (!TitleChart.isEmpty())
    {
        if (!Label.isEmpty())
            VHQt_Result+="\\caption{"+TitleChart+"}\\label{"+Label+"}\n";
        else
            VHQt_Result+="\\caption{"+TitleChart+"}\n";
    }
    else
    {
        if (!Label.isEmpty())
            VHQt_Result+="\\caption{График}\\label{"+Label+"}\n";
        else
            VHQt_Result+="\\caption{График}\n";
    }
    if (ForNormalSize) VHQt_Result+="\\end{figure}\n";

    delete [] Temp_VHQt_VectorX;
    delete [] Temp_VHQt_VectorY1;
    delete [] Temp_VHQt_VectorY2;

    return VHQt_Result;
}
//---------------------------------------------------------------------------
template <class T> QString THQt_LatexShowTwoChartsOfLine (T *VHQt_VectorX,T *VHQt_VectorY1,T *VHQt_VectorY2, int VHQt_N, QString TitleChart, QString NameVectorX, QString NameVectorY,QString NameLine1, QString NameLine2, QString Label,bool ShowLine,bool ShowPoints,bool ShowArea,bool ShowSpecPoints, bool ForNormalSize)
{
    /*
    Функция возвращает строку с выводом некоторого двух графиков по точкам с Latex кодами. У обоих графиков одинаковый массив значений X. По сравнению с основной функцией тут отсутствует параметр GrayStyle.
    Входные параметры:
     VHQt_VectorX - указатель на вектор координат X точек;
     VHQt_VectorY1 - указатель на вектор координат Y точек первой линии;
     VHQt_VectorY2 - указатель на вектор координат Y точек второй линии;
     VHQt_N - количество точек;
     TitleChart - заголовок графика;
     NameVectorX - название оси Ox. В формате: [обозначение], [расшифровка]. Например: u, Вероятность выбора;
     NameVectorY - название оси Oy. В формате: [обозначение], [расшифровка]. Например: q, Количество абрикосов;
     NameLine1 - название первого графика (для легенды);
     NameLine2 - название второго графика (для легенды);
     Label - label для графика;
     ShowLine - показывать ли линию;
     ShowPoints - показывать ли точки;
     ShowArea - показывать ли закрашенную область под кривой;
     ShowSpecPoints - показывать ли специальные точки;
     ForNormalSize - нормальный размер графика (на всю ширину) или для маленького размера график создается.
    Возвращаемое значение:
     Строка с Latex кодами с выводимым графиком.
    */
    QString VHQt_Result;//переменная итогового результата

    VHQt_Result = THQt_LatexShowTwoChartsOfLine (VHQt_VectorX,VHQt_VectorY1,VHQt_VectorY2, VHQt_N, TitleChart, NameVectorX, NameVectorY, NameLine1, NameLine2, Label, ShowLine, ShowPoints, ShowArea, ShowSpecPoints, ForNormalSize, false);

    return VHQt_Result;
}
//---------------------------------------------------------------------------
template <class T> QString THQt_LatexShowTwoChartsOfLine (T *VHQt_VectorX,T *VHQt_VectorY1,T *VHQt_VectorY2, int VHQt_N, QString TitleChart, QString NameVectorX, QString NameVectorY,QString NameLine1, QString NameLine2, QString Label,bool ShowLine,bool ShowPoints,bool ShowArea,bool ShowSpecPoints)
{
    /*
    Функция возвращает строку с выводом некоторого двух графиков по точкам с Latex кодами. У обоих графиков одинаковый массив значений X. По сравнению с основной функцией тут отсутствует параметр ForNormalSize.
    Входные параметры:
     VHQt_VectorX - указатель на вектор координат X точек;
     VHQt_VectorY1 - указатель на вектор координат Y точек первой линии;
     VHQt_VectorY2 - указатель на вектор координат Y точек второй линии;
     VHQt_N - количество точек;
     TitleChart - заголовок графика;
     NameVectorX - название оси Ox. В формате: [обозначение], [расшифровка]. Например: u, Вероятность выбора;
     NameVectorY - название оси Oy. В формате: [обозначение], [расшифровка]. Например: q, Количество абрикосов;
     NameLine1 - название первого графика (для легенды);
     NameLine2 - название второго графика (для легенды);
     Label - label для графика;
     ShowLine - показывать ли линию;
     ShowPoints - показывать ли точки;
     ShowArea - показывать ли закрашенную область под кривой;
     ShowSpecPoints - показывать ли специальные точки.
    Возвращаемое значение:
     Строка с Latex кодами с выводимым графиком.
    */
    QString VHQt_Result;//переменная итогового результата

    VHQt_Result = THQt_LatexShowTwoChartsOfLine (VHQt_VectorX,VHQt_VectorY1,VHQt_VectorY2, VHQt_N, TitleChart, NameVectorX, NameVectorY, NameLine1, NameLine2, Label, ShowLine, ShowPoints, ShowArea, ShowSpecPoints,true,false);

    return VHQt_Result;
}
//---------------------------------------------------------------------------
template <class T> QString THQt_LatexShowTwoChartsOfLine (T *VHQt_VectorX,T *VHQt_VectorY1,T *VHQt_VectorY2, int VHQt_N, QString TitleChart, QString NameVectorX, QString NameVectorY,QString NameLine1, QString NameLine2, QString Label)
{
    /*
    Функция возвращает строку с выводом некоторого двух графиков по точкам с Latex кодами. У обоих графиков одинаковый массив значений X. По сравнению с основной функцией тут отсутствует параметр ForNormalSize и RedLine и все остальные булевские переменные.
    Входные параметры:
     VHQt_VectorX - указатель на вектор координат X точек;
     VHQt_VectorY1 - указатель на вектор координат Y точек первой линии;
     VHQt_VectorY2 - указатель на вектор координат Y точек второй линии;
     VHQt_N - количество точек;
     TitleChart - заголовок графика;
     NameVectorX - название оси Ox. В формате: [обозначение], [расшифровка]. Например: u, Вероятность выбора;
     NameVectorY - название оси Oy. В формате: [обозначение], [расшифровка]. Например: q, Количество абрикосов;
     NameLine1 - название первого графика (для легенды);
     NameLine2 - название второго графика (для легенды);
     Label - label для графика.
    Возвращаемое значение:
     Строка с Latex кодами с выводимым графиком.
    */
    QString VHQt_Result;//переменная итогового результата

    VHQt_Result = THQt_LatexShowTwoChartsOfLine (VHQt_VectorX,VHQt_VectorY1,VHQt_VectorY2, VHQt_N, TitleChart, NameVectorX, NameVectorY, NameLine1, NameLine2, Label, true, true, true, true,true,false);

    return VHQt_Result;
}
//---------------------------------------------------------------------------
template <class T> QString THQt_LatexShowTwoChartsOfLine (T *VHQt_VectorX,T *VHQt_VectorY1,T *VHQt_VectorY2, int VHQt_N)
{
    /*
    Функция возвращает строку с выводом некоторого двух графиков по точкам с Latex кодами. У обоих графиков одинаковый массив значений X. По сравнению с основной функцией тут отсутствует параметр ForNormalSize и RedLine и все остальные булевские переменные, а также все переменные названий.
    Входные параметры:
     VHQt_VectorX - указатель на вектор координат X точек;
     VHQt_VectorY1 - указатель на вектор координат Y точек первой линии;
     VHQt_VectorY2 - указатель на вектор координат Y точек второй линии;
     VHQt_N - количество точек;
     TitleChart - заголовок графика;
     NameVectorX - название оси Ox. В формате: [обозначение], [расшифровка]. Например: u, Вероятность выбора;
     NameVectorY - название оси Oy. В формате: [обозначение], [расшифровка]. Например: q, Количество абрикосов;
     NameLine1 - название первого графика (для легенды);
     NameLine2 - название второго графика (для легенды);
     Label - label для графика.
    Возвращаемое значение:
     Строка с Latex кодами с выводимым графиком.
    */
    QString VHQt_Result;//переменная итогового результата

    VHQt_Result = THQt_LatexShowTwoChartsOfLine (VHQt_VectorX,VHQt_VectorY1,VHQt_VectorY2, VHQt_N, "", "x", "y", "График 1", "График 2", "Chart"+HQt_RandomString(8), true, true, true, true,true,false);

    return VHQt_Result;
}