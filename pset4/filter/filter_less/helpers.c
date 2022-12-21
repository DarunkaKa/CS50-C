#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
//повторювати кожен стовпець пікселя
    for (int i = 0; i < height; i++)                             
    {
        //повторювати кожен рядок пікселя в кожному стовпці
        for (int j = 0; j < width; j++)
        {
            //отримати значення кожного кольору
            int rd = image[i][j].rgbtRed;
            int be = image[i][j].rgbtBlue;
            int gn = image[i][j].rgbtGreen;
            //обчислити середнє значення кожного пікселя та округлити
            int mat = round(((float)rd + (float)be + (float)gn) / 3);
            //поставити середнє значення, як нове значення кожного пікселя
            image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = mat;
        }
    }
    return;
}

//діапазон допустимих значень
int max(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = max(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = max(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = max(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //Тимчасовий масив для зберігання елеменітів у лівій стороні
            int row[3];
            
            //поміняти місцямии пікселі зправа на ліво
            row[0] = image[i][j].rgbtRed;
            row[1] = image[i][j].rgbtGreen;
            row[2] = image[i][j].rgbtBlue;
            
            //Поміняти праву половину лівою (середній піксель незмінний якщо непарний рядок)
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            
            //вставлення елементів  назад у праву сторону
            image[i][width - j - 1].rgbtRed = row[0];
            image[i][width - j - 1].rgbtGreen = row[1];
            image[i][width - j - 1].rgbtBlue = row[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
//створити тимчасовий новий масив
    RGBTRIPLE ar[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ar[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rd = 0;
            int gn = 0;
            int be = 0;
            float var = 0;
//кути
            //нижній правий кут
            if (i >= 0 && j >= 0)
            {
                rd += ar[i][j].rgbtRed;
                gn += ar[i][j].rgbtGreen;
                be += ar[i][j].rgbtBlue;
                var++;
            }
            //нижній лівий кут
            if (i >= 0 && j - 1 >= 0)
            {
                rd += ar[i][j - 1].rgbtRed;
                gn += ar[i][j - 1].rgbtGreen;
                be += ar[i][j - 1].rgbtBlue;
                var++;
            }
            //верхній лівий кут
            if (i - 1 >= 0 && j >= 0)
            {
                rd += ar[i - 1][j].rgbtRed;
                gn += ar[i - 1][j].rgbtGreen;
                be += ar[i - 1][j].rgbtBlue;
                var++;
            }
            //правий верхній кут
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                rd += ar[i - 1][j - 1].rgbtRed;
                gn += ar[i - 1][j - 1].rgbtGreen;
                be += ar[i - 1][j - 1].rgbtBlue;
                var++;
            }
//4 краї
            //нижній край
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                rd += ar[i][j + 1].rgbtRed;
                gn += ar[i][j + 1].rgbtGreen;
                be += ar[i][j + 1].rgbtBlue;
                var++;
            }
            //верхній край
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                rd += ar[i - 1][j + 1].rgbtRed;
                gn += ar[i - 1][j + 1].rgbtGreen;
                be += ar[i - 1][j + 1].rgbtBlue;
                var++;
            }
            //лівий край
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                rd += ar[i + 1][j].rgbtRed;
                gn += ar[i + 1][j].rgbtGreen;
                be += ar[i + 1][j].rgbtBlue;
                var++;
            }
            //правий край
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                rd += ar[i + 1][j - 1].rgbtRed;
                gn += ar[i + 1][j - 1].rgbtGreen;
                be += ar[i + 1][j - 1].rgbtBlue;
                var++;
            }
//середина
            //середні
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                rd += ar[i + 1][j + 1].rgbtRed;
                gn += ar[i + 1][j + 1].rgbtGreen;
                be += ar[i + 1][j + 1].rgbtBlue;
                var++;
            }
            //середнє значення кольору
            image[i][j].rgbtRed = round(rd / var);
            image[i][j].rgbtGreen = round(gn / var);
            image[i][j].rgbtBlue = round(be / var);
        }
    }
    return;
}
