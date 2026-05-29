# Global Tritium Scenarios
Attempt to recreate global tritium supply graphs found in the literature.

## Assumptions for All Scenarios
* Tritium production begins in 1971.
* The power from 2017 was used for each reactor to calculate a tritium production factor.
* Used data accessible from the IAEA PRIS Landing Page
* Used first grid connection date for the startup date to get <build_time>.
* For each reactor the operating history was used to calculate tritium production rates from the annual data.
* Tritium [kg] = Electricity Supplied [GWh] x 0.228 [kg/GWe] x 0.9 x➗ Annual Time On-line [h]
* Averaged these values from start year to 2017 and divided by 12 for monthly production rate.  
* Years of very low or 0 production were omitted from average calculation.
* Years of no production were omitted from the model.

## Kovari (Moderate) Scenario Assumptions
Canadian Tritium
* Canadian units will operate for 30 years from first connection to the grid or 25 years following refurbishment.
* Bruce 3-6 and Darlington 1-4 are refurbished according to schedule.
* Canadian tritium sales of 0.3 kg/year.

Korean Tritium 
*	Wolsong 1-4 will run for 30 years from first connection to the grid.
*	Wolsong 1 was permanently shut down in 2022.
*	Wolsong 2 is refurbished after 30 years.

Romanian Tritium 
* A tritium removal facility is built in Romania.
* Cernavoda 1 and 2 are refurbished after 30 years.

## Kovari (Optimistic) Scenario Assumptions
Canadian Tritium
* Canadian units will operate for 30 years from first connection to the grid or 25 years following refurbishment.
* All Darlington and Bruce units are refurbished according to schedule.
* Canadian tritium sales of 0.2 kg/year.

Korean Tritium 
*	Wolsong 1-4 will run for 30 years from first connection to the grid.
*	Wolsong 1 was permanently shut down in 2022.
*	Wolsong 2-4 are refurbished after 30 years.

Romanian Tritium 
* A tritium removal facility is built in Romania in mid 2020s.
* Cernavoda 1 and 2 are refurbished as scheduled.
* Cernavoda 3 and 4 are constructed as scheduled and refurbished after 30 years.
