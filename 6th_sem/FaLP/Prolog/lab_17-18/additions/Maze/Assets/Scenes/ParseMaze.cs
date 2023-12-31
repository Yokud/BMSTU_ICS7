using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class ParseMaze : MonoBehaviour
{
    public string mazeSrc;

    public GameObject wall, floor, trap, start, finish;

    // Start is called before the first frame update
    void Start()
    {
        if (string.IsNullOrEmpty(mazeSrc))
            throw new Exception("No maze!\n");

        string[] vals = mazeSrc.Substring(1, mazeSrc.Length - 2).Split(',');

        for (int i = 0; i < vals.Length; i++)
            vals[i] = vals[i].Trim(new char[] {']', '['});

        int n = (int)Math.Sqrt(vals.Length);

        float coef = 3.25f;
        for (int i = 0; i < vals.Length; i++)
        {
            switch (vals[i])
            {
                case "W":
                    Instantiate(wall, new Vector3((i / n) * coef, (i % n) * coef, 0), Quaternion.identity);
                    break;

                case "O":
                    Instantiate(floor, new Vector3((i / n) * coef, (i % n) * coef, 0), Quaternion.identity);
                    break;

                case "T":
                    Instantiate(trap, new Vector3((i / n) * coef, (i % n) * coef, 0), Quaternion.identity);
                    break;

                case "S":
                    Instantiate(start, new Vector3((i / n) * coef, (i % n) * coef, 0), Quaternion.identity);
                    break;

                case "F":
                    Instantiate(finish, new Vector3((i / n) * coef, (i % n) * coef, 0), Quaternion.identity);
                    break;
            }
        }

        for (int i = -1; i < n + 1; i++)
            for (int j = -1; j < n + 1; j++)
                if (i == -1 || i == n)
                    Instantiate(wall, new Vector3(i * coef, j * coef, 0), Quaternion.identity);
                else if (j == -1 || j == n)
                    Instantiate(wall, new Vector3(i * coef, j * coef, 0), Quaternion.identity);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
