scrape_configs:
- job_name: system
  static_configs:
  - targets:
      - localhost
    labels:
      job: syslogs
      __path__: /var/log/syslog
