### Programação Concorrente - 2023.1

# Resultados das execuções do algoritmo Concorrente e Sequencial de Merge Sort

## Clayton Junior da Silva Portal - 117256689 
## Paulo Henrique de França Araujo Cunha - 117277009

#### obs: Ganho = Tsequencial / Tconcorrente


### *1000 elementos:*

| Rodada | Merge Sort Concorrente (NTHREADS = 2) |      Merge Sort Sequencial      |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.0002570000 segundos         |      0.0001400000 segundos      |
|   2    |         0.0001150000 segundos         |      0.0001680000 segundos      |
|   3    |         0.0001170000 segundos         |      0.0001750000 segundos      |
|   4    |         0.0002230000 segundos         |      0.0001770000 segundos      |
|   5    |         0.0001120000 segundos         |      0.0001730000 segundos      |
| Média  |    0.00016480000000000002 segundos    | 0.00016659999999999998 segundos |

**Ganho com 2 threads:** 1.010922330097087 segundos.


| Rodada | Merge Sort Concorrente (NTHREADS = 4) |      Merge Sort Sequencial      |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.0006410000 segundos         |      0.0001440000 segundos      |
|   2    |         0.0001940000 segundos         |      0.0001370000 segundos      |
|   3    |         0.0002000000 segundos         |      0.0001350000 segundos      |
|   4    |         0.0002140000 segundos         |      0.0001500000 segundos      |
|   5    |         0.0001860000 segundos         |      0.0001780000 segundos      |
| Média  |		0.00028700000000000004 segundos		 | 0.00014879999999999998 segundos |

**Ganho com 4 threads:** 0.5184668989547037 segundos.


### *10K elementos:*

| Rodada | Merge Sort Concorrente (NTHREADS = 2) |			Merge Sort Sequencial			 |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.0011520000 segundos         |  		0.0021410000 segundos			 |
|   2    |         0.0002700000 segundos         |			0.0018470000 segundos			 |
|   3    |         0.0002700000 segundos         |			0.0021470000 segundos			 |
|   4    |         0.0002820000 segundos         |			0.0022800000 segundos			 |
|   5    |         0.0003030000 segundos         |			0.0017840000 segundos			 |
| Média  |					0.0004554 segundos					 |			 0.0020398 segundos				 |

**Ganho com 2 threads:** 4.479139218269653 segundos.

| Rodada | Merge Sort Concorrente (NTHREADS = 4) |			Merge Sort Sequencial			 |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.0016230000 segundos         |			0.0019740000 segundos			 |
|   2    |         0.0012670000 segundos         |			0.0026680000 segundos			 |
|   3    |         0.0010940000 segundos         |			0.0022170000 segundos			 |
|   4    |         0.0010760000 segundos         |			0.0023840000 segundos			 |
|   5    |         0.0014100000 segundos         |			0.0020740000 segundos			 |
| Média  |		0.0012939999999999998 segundos		 |			 0.0022634 segundos				 |

**Ganho com 4 threads:** 1.7491499227202476 segundos.


### *100K elementos:*

| Rodada | Merge Sort Concorrente (NTHREADS = 2) |			Merge Sort Sequencial			 |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.0188430000 segundos         |			0.0228570000 segundos			 |
|   2    |         0.0156250000 segundos         |			0.0224480000 segundos			 |
|   3    |         0.0215590000 segundos         |			0.0244120000 segundos			 |
|   4    |         0.0176760000 segundos         |			0.0233380000 segundos			 |
|   5    |         0.0170960000 segundos         |			0.0225750000 segundos			 |
| Média  |		0.018159799999999997 segundos			 |				0.023126 segundos				 |

**Ganho com 2 threads:** 1.2734721748036875 segundos.

| Rodada | Merge Sort Concorrente (NTHREADS = 4) |			Merge Sort Sequencial			 |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.0239280000 segundos         |			0.0257200000 segundos			 |
|   2    |         0.0257870000 segundos         |			0.0247990000 segundos			 |
|   3    |         0.0176070000 segundos         |			0.0250890000 segundos			 |
|   4    |         0.0259070000 segundos         |			0.0259860000 segundos			 |
|   5    |         0.0103090000 segundos         |			0.0227930000 segundos			 |
| Média  |					0.0207076 segundos					 |				0.0248774 segundos			 |

**Ganho com 4 threads:** 1.2013656821650023 segundos.


### *1M elementos:*

| Rodada | Merge Sort Concorrente (NTHREADS = 2) |			Merge Sort Sequencial			 |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.2768260000 segundos         |			0.2531750000 segundos			 |
|   2    |         0.2799290000 segundos         |			0.2461610000 segundos			 |
|   3    |         0.2998340000 segundos         |			0.2489030000 segundos			 |
|   4    |         0.2932870000 segundos         |			0.2564630000 segundos			 |
|   5    |         0.2789660000 segundos         |			0.2584260000 segundos			 |
| Média  |			0.28576840000000003 segundos		 |				0.2526256 segundos			 |

**Ganho com 2 threads:** 0.8840221662017214 segundos.

| Rodada | Merge Sort Concorrente (NTHREADS = 4) |			Merge Sort Sequencial			 |
|--------|---------------------------------------|---------------------------------|
|   1    |         0.3371010000 segundos         |			0.2460490000 segundos			 |
|   2    |         0.3298240000 segundos         |			0.2505880000 segundos			 |
|   3    |         0.3543830000 segundos         |			0.2463560000 segundos			 |
|   4    |         0.3360900000 segundos         |			0.2434830000 segundos			 |
|   5    |         0.3347170000 segundos         |			0.2525980000 segundos			 |
| Média  |					 0.338423 segundos					 |				0.2478148 segundos			 |

**Ganho com 4 threads:** 0.7322634690904578 segundos.
