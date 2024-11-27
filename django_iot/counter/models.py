from django.db import models

class Metric(models.Model):
    name = models.CharField(max_length=50, default = "counter")
    intensity = models.CharField(max_length=30)
    voltage = models.CharField(max_length=30)
    power = models.CharField(max_length=30)
    energy = models.CharField(max_length=30)

    class Meta:
        verbose_name = 'Metric'
        verbose_name_plural = 'Metrics'

    def __str__(self):
        return self.name