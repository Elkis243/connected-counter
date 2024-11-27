from rest_framework import serializers
from .models import Metric

class Metric_Serializer(serializers.ModelSerializer):
    class Meta:
        model = Metric
        fields = ('name', 'intensity', 'voltage', 'power', 'energy')