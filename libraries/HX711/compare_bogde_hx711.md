
## API comparison API Bogde vs this HX711 library

library is based upon 0.7.3 of Bogde.

Main differences:
- HX711 supports more modi for reading.
- HX711 has more convenience functions.
- HX711 uses floats internally.
- Bogde is more sophisticated, ATOMIC/ FASTCPU and boards and builds.
- Bogde has pre 1.0 support.


### Table API comparison

Indicative


|  function            |  Bogde 0.7.5  |  HX711 0.6.6  |  notes  |
|:---------------------|:-------------:|:-------------:|:-------:|
|  begin               |       V       |       V       |
|  reset               |               |       V       |  internal variables
|                      |               |       V       |
|  is_ready            |       V       |       V       |
|  wait_ready          |       V       |       V       |
|  wait_ready_retry    |       V       |       V       |
|  wait_ready_timeout  |       V       |       V       |
|                      |               |               |
|  read                |       V       |       V       |  returns float iso long
|  read_average        |       V       |       V       |  returns float iso long
|  read_median         |               |       V       |  extra modi 
|  read_medavg         |               |       V       |  extra modi 
|  read_runavg         |               |       V       |  extra modi 
|                      |               |               |
|  get_value           |       V       |       V       |  float iso double
|  get_units           |       V       |       V       |
|                      |               |               |
|  set_raw_mode        |               |       V       |  extra modi
|  set_average_mode    |               |       V       |  extra modi
|  set_median_mode     |               |       V       |  extra modi
|  set_medavg_mode     |               |       V       |  extra modi
|  set_runavg_mode     |               |       V       |  extra modi
|  get_mode            |               |       V       |  extra modi
|                      |               |               |
|  tare                |       V       |       V       |
|  get_tare            |               |       V       |  convenience function.
|  tare_set            |               |       V       |  convenience function.
|                      |               |               |
|  set_gain            |       V       |       V       |  bool iso void (error)
|  get_gain            |               |       V       |  convenience function.
|  set_scale           |       V       |       V       |  bool iso void (error)
|  get_scale           |       V       |       V       |
|  set_offset          |       V       |       V       |
|  get_offset          |       V       |       V       |
|                      |               |               |
|  calibrate_scale     |               |       V       |  convenience function.
|                      |               |               |
|  power_down          |       V       |       V       |
|  power_up            |       V       |       V       |
|  last_read           |               |       V       |  time stamp (obsolete in future)
|  last_time_read      |               |       V       |  time stamp
|                      |               |               |
|  set_rate_pin        |               |       V       |  only if rate pin is exposed.
|  set_rate_10SPS      |               |       V       |
|  set_rate_80SPS      |               |       V       |
|  get_rate            |               |       V       |
|                      |               |               |
|  getLastError        |               |       V       |  new 0.6.6
|                      |               |               |
|  get_price           |               |       V       |  application code
|  set_unit_price      |               |       V       |  application code
|  get_unit_price      |               |       V       |  application code
|                      |               |               |

