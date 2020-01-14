with open('data/ca_languages.csv', 'r') as f:
    for line in f:
        data = line.strip("\n").split(",") # clean data down
        try:
            (year, language, count) = (int(data[0]), data[1], int(data[2]))
            print(year, language, count)
            
        except:
            pass
