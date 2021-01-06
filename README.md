# Autodock Vina Extractor
This is for [AutoDock Vina](http://vina.scripps.edu/) to extract the model data<br>

## Environments
- gcc 12.0.0
- cmake 3.19.2


## Usage
```
$ git clone https://github.com/Tiger-0512/autodock-vina-extractor.git
$ sh run.sh
```

## Note
If you use your own data,
- Change the `fname` in `data_extractor.c` to your own file path.
- Change the `model_len` in `data_extractor.c` to your model's length.

If you don't change the `fname` and `model_len`, You can try the example with test data.
