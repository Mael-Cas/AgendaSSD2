#include "pbPlots.h"
#include "supportLib.h"
#include "../timer.h"
#include "../list.h"





int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

void TestTimer(int n, int numberOfSearch, int* opti, int* nopti) {
    t_level_list *list = createLevelList();
    int max_val = pow(2, n);
    max_val--;
    for (int lvl = 0; lvl < n; lvl++) {
        for (int val = 1; val < max_val + 1; val++) {
            int modulo = pow(2, (lvl + 1));
            if ((val % modulo)) {
                InsertLevelList(list, val, lvl);
            }
        }
    }
    int valToSearch;

    startTimer();
    for(int i = 0; i < numberOfSearch ; i++){
        valToSearch = randomInRange(1, 512);
        searchInList(list, valToSearch);
    }
    stopTimer();

    *opti = getTimeAsMsecs();
    startTimer();
    for(int i = 0; i < numberOfSearch ; i++){
        valToSearch = randomInRange(1, 512);
        classicSearchInList(list, valToSearch);
    }
    stopTimer();
    *nopti = getTimeAsMsecs();
}

int main() {

    double xs[4];
    double ys[4];

    double xs2[4];
    double ys2[4];
    int opti, nopti;

    srand(time(NULL));

    printf("For 1 000 : \n");
    TestTimer(5, 1000, &opti, &nopti);
    xs[0] = opti;
    ys[0] = 1000;
    xs2[0] = nopti;
    ys2[0] = 1000;
    printf("\n");
    printf("For 10 000 : \n");
    TestTimer(5, 10000, &opti, &nopti);
    xs[1] = opti;
    ys[1] = 10000;
    xs2[1] = nopti;
    ys2[1] = 10000;
    printf("\n");
    printf("For 100 000 : \n");
    TestTimer(5, 100000, &opti, &nopti);
    xs[2] = opti;
    ys[2] = 100000;
    xs2[2] = nopti;
    ys2[2] = 100000;
    printf("\n");
    printf("For 1 000 000 : \n");
    TestTimer(5, 1000000, &opti, &nopti);
    xs[3] = opti;
    ys[3] = 1000000;
    xs2[3] = nopti;
    ys2[3] = 1000000;


    _Bool success;
    StringReference *errorMessage;

    StartArenaAllocator();

    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();


    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = xs;
    series->xsLength = sizeof(xs) / sizeof(double);
    series->ys = ys;
    series->ysLength = sizeof(ys) / sizeof(double);
    series->linearInterpolation = true;
    series->pointType = L"solid";
    series->pointTypeLength = wcslen(series->lineType);
    series->lineThickness = 2;
    series->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = xs2;
    series2->xsLength = sizeof(xs2) / sizeof(double);
    series2->ys = ys2;
    series2->ysLength = sizeof(ys2) / sizeof(double);
    series2->linearInterpolation = true;
    series2->lineType = L"solid";
    series2->lineTypeLength = wcslen(series->lineType);
    series2->lineThickness = 2;
    series2->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1200;
    settings->height = 800;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = L"";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"temps en ms";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"répétition";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s[] = {series, series2};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 2;

    errorMessage = (StringReference *) malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if (success) {
        ByteArray *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "example4.png");
        DeleteImage(imageReference->image);
    } else {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++) {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

    FreeAllocations();

    return success ? 0 : 1;
}