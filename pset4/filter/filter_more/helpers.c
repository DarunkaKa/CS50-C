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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    //оператор Собеля
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //по рядках
    for (int i = 0; i < height; i++)
    {
        //по стовпцях
        for (int j = 0; j < width; j++)
        {
            float Gx_rd;
            float Gx_gr;
            float Gx_be;
            float Gy_rd;
            float Gy_gr;
            float Gy_be;
            Gx_rd = Gx_gr = Gx_be = 0;
            Gy_rd = Gy_gr = Gy_be = 0;
            //для кожного пікселя по вертикалі і по горизонталі
            for (int d = -1; d < 2; d++)
            {
                for (int k = -1; k < 2; k++)
                {
                    //перевірка наявності пікселя всередині рядка
                    if (i + d < 0 || i + d >= height)
                    {
                        continue;
                    }
                    //перевірка наявності пікселя всередині стовпця
                    if (j + k < 0 || j + k >= width)
                    {
                        continue;
                    }
                    Gx_rd += ar[i + d][j + k].rgbtRed * Gx[d + 1][k + 1];
                    Gx_gr += ar[i + d][j + k].rgbtGreen * Gx[d + 1][k + 1];
                    Gx_be += ar[i + d][j + k].rgbtBlue * Gx[d + 1][k + 1];
                    Gy_rd += ar[i + d][j + k].rgbtRed * Gy[d + 1][k + 1];
                    Gy_gr += ar[i + d][j + k].rgbtGreen * Gy[d + 1][k + 1];
                    Gy_be += ar[i + d][j + k].rgbtBlue * Gy[d + 1][k + 1];
                }
            }
            int red = (int)round(sqrt(Gx_rd * Gx_rd + Gy_rd * Gy_rd));
            int green = (int)round(sqrt(Gx_gr * Gx_gr + Gy_gr * Gy_gr));
            int blue = (int)round(sqrt(Gx_be * Gx_be + Gy_be * Gy_be));
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
